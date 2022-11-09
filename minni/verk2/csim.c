/*
 * csim.c - A cache simulator that can replay traces from Valgrind
 *     and output statistics such as number of hits, misses, and
 *     evictions.  The replacement policy is LRU.
 *
 * Implementation and assumptions:
 *  1. Each load/store can cause at most one cache miss. (I examined the trace,
 *     the largest request I saw was for 8 bytes).
 *  2. Instruction loads (I) are ignored, since we are only interested in evaluating
 *     data cache performance.
 *  3. Data modify (M) is treated as a load followed by a store to the same
 *     address. Hence, an M operation can result in two cache hits, or a miss and a
 *     hit plus an possible eviction.
 *
 */
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

/* Type: Memory address */
typedef unsigned long long int mem_addr_t;

/* Hér fyrir neðan eru ýmsar víðværar breytur skilgreindar.  Þið munuð nota þessar
   en þurfið líka að bæta við nokkrum í viðbót (t.d. skilgreiningu á línu og
   skilgreiningu á skyndiminninu sjálfu)
*/

/* Globals set by command line args */
int s = 0; /* set index bits */
int b = 0; /* block offset bits */
int E = 0; /* associativity */
char *trace_file = NULL;

/* Derived from command line args */
int S; /* number of sets */
int B; /* block size (bytes) */

/* Counters used to record cache statistics */
int miss_count = 0;
int hit_count = 0;
int eviction_count = 0;
unsigned long long int lru_counter = 1;

/**
 * @brief skilgreining á einni línu í block
 */
typedef struct line
{
    char valid;             /**bita gildi, 0 ef lína ekki lögleg, 1 ef hún er lögleg*/
    mem_addr_t tag;         /**efstu bitar í visfangi línunar*/
    unsigned long long lru; /**teljari sem segir til um hvenær þessi lína var síðust notuð*/
} Line;

typedef Line *Set;  /**skilgreining á set, fylki af línum*/
typedef Set *Cache; /**skilgreining á skyndiminninu, fylki af mengjum*/
Cache cache;        /**global breyta cache*/

/*
 * initCache - Allocate memory, write 0's for valid and tag and LRU
 */
void initCache()
{
    // frumstilla skyndiminni sem fylki af mengjum
    cache = (Set *)malloc(sizeof(Set *) * S);

    // lykkja yfir skyndiminnið til að frumstilla mengin
    for (int i = 0; i < S; i++)
    {
        cache[i] = (Line *)malloc(sizeof(Line *) * B);
        for (int j = 0; j < E; j++)
        {
            // frumstilla gögin fyrir hverja línu
            cache[i][j].valid = 0;
            cache[i][j].tag = 0;
            cache[i][j].lru = 0;
        }
    }
}

/*
 * freeCache - free allocated memory
 */
void freeCache()
{
    // segir sig pínu sjálft
    // fer í gegnum öll mengi skyndiminnisins og hreinsar það minnisfang
    for (int i = 0; i < S; i++)
    {
        free(cache[i]);
    }
    // endar á að hreinsa skyndiminnið skjálft
    free(cache);
}

/*
 * accessData - Access data at memory address addr.
 *   If it is already in cache, increast hit_count
 *   If it is not in cache, bring it in cache, increase miss count.
 *   Also increase eviction_count if a line is evicted.
 */
void accessData(mem_addr_t addr)
{
    // temp lru gildi sett sem stærsta gildi á int
    // síðan lykkjað yfir öll lru gildi í cachinu og minnsta fundið
    long int shortest_lru = ULONG_MAX;
    int CLlru; /**current longest lru*/

    // sett vísun á viðeigandi stað í skyndiminni
    // hliðrað til hægri um línustærð og logical &
    // við stærð skyndiminnis til að fá viðeigandi minnisfang
    mem_addr_t setI = addr >> b & (mem_addr_t)(S - 1);

    // passað að taggið sé á sama formi og Line.tag
    mem_addr_t tag = addr >> (s + b);
    Set setInUse = cache[setI];

    for (int i = 0; i < E; ++i)
    {
        if (setInUse[i].valid && setInUse[i].tag == tag)
        {
            setInUse[i].lru = lru_counter++;
            hit_count++;
            return;
        }

        // gott að nota bara sömu lykkju til að gera tvo alveg mismunandi hluti
        // það eykur performance :) :)
        if (setInUse[i].lru < shortest_lru)
        {
            shortest_lru = setInUse[i].lru;
            CLlru = i;
        }
    }

    miss_count++;

    if (setInUse[CLlru].valid)
    {
        eviction_count++;
    }
    setInUse[CLlru].valid = 1;
    setInUse[CLlru].lru = lru_counter++;
    setInUse[CLlru].tag = tag;
}

/*
 * replayTrace - replays the given trace file against the cache
 */
void replayTrace(char *trace_fn)
{
    char buf[1000];
    mem_addr_t addr = 0;
    unsigned int len = 0;
    FILE *trace_fp = fopen(trace_fn, "r");

    if (!trace_fp)
    {
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }

    while (fgets(buf, 1000, trace_fp) != NULL)
    {
        if (buf[1] == 'S' || buf[1] == 'L' || buf[1] == 'M')
        {
            sscanf(buf + 3, "%llx,%u", &addr, &len);

            accessData(addr);

            /* If the instruction is R/W then access again */
            if (buf[1] == 'M')
                accessData(addr);
        }
    }

    fclose(trace_fp);
}

/*
 * printSummary - Summarize the cache simulation statistics
 */
void printSummary(int hits, int misses, int evictions)
{
    printf("hits:%d  misses:%d  evictions:%d\n", hits, misses, evictions);
    printf("miss ratio: %.2f%%\n", 100.0 * misses / (hits + misses));
}

/*
 * printUsage - Print usage info
 */
void printUsage(char *argv[])
{
    printf("Usage: %s [-h] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/*
 * main - Main routine
 */
int main(int argc, char *argv[])
{
    char c;

    while ((c = getopt(argc, argv, "s:E:b:t:h")) != -1)
    {
        switch (c)
        {
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }

    /* Make sure that all required command line args were specified */
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL)
    {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }

    /* Compute S, E and B from command line args */
    S = (unsigned int)(1 << s);
    B = (unsigned int)(1 << b);

    /* Initialize cache */
    initCache();

    /* Run the simulation */
    replayTrace(trace_file);

    /* Free allocated memory */
    freeCache();

    /* Output the hit and miss statistics */
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
