// |||||||||||||||||||||||||||||||||
// ||    __    sjomli.is    __    ||
// ||  _/  |_ __ __  _____ |__|   ||
// ||  \   __\  |  \/     \|  |   ||
// ||   |  | |  |  /  Y Y  \  |   ||
// ||   |__| |____/|__|_|__/__|   ||
// ||                             ||
// |||||||||||||||||||||||||||||||||

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

/* Prentar út stökin í tengdum list */
void printList(struct Node *h)
{
    printf("Listi: ");
    while (h != NULL)
    {
        printf("%d", h->data);
        h = h->next;
        if (h != NULL)
            printf(" -> ");
    }
    printf("\n");
}

/* Eyðir hnúti númer k í tengda listanum sem head bendir á.
   Skilar bendi á fremsta hnút listans                     */
struct Node *delNode(struct Node *head, int k)
{
    struct Node *p, *q;
    if (k == 1 && head->next != NULL)
    {
        p = head->next;
        free(head);
        head = p;
        return head;
    };

    p = head;
    q = p->next;
    int i;
    for (i = 1; i < k; i++)
    {
        // printf("%i: %i, %i \n", i, p->data,q->data);
        if (q->next != NULL)
        {
            p = q;
            q = q->next;
        }
        else
            break;
    }
    if (i == k && p->next->next != NULL)
    {
        p->next = p->next->next;
        free(q);
    }

    return head;
}

/* Býr til n-staka lista með slembigildum (0 til 99),
   skilar bendi á fremsta hnút, eða NULL ef n < 1 */
struct Node *createList(int n)
{
    struct Node *head, *p;
    int i;

    /* Ef n er núll eða minna þá tómur listi */
    if (n < 1)
        return NULL;

    /* Búa til fyrsta hnútinn og láta head benda á hann */
    head = p = (struct Node *)malloc(sizeof(struct Node));
    head->data = rand() % 100;
    head->next = NULL;

    /* Búa til restina af hnútunum */
    for (i = 1; i < n; i++)
    {
        p = (struct Node *)malloc(sizeof(struct Node));
        p->data = rand() % 100;
        p->next = head;
        head = p;
    }

    return head;
}

int main(int argc, char **argv)
{
    struct Node *list;

    /* Búa til listann með 10 slembigildum */
    list = createList(10);
    printList(list);

    /* Eyða út nokkrum hnútum og skoða listann í hvert sinn */
    list = delNode(list, 1);
    printList(list);

    list = delNode(list, 3);
    printList(list);

    list = delNode(list, 20);
    printList(list);

    return 0;
}