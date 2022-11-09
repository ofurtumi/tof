from subprocess import call, check_output
import pandas as pd

file = input("Hvaða skrá viltu opna: ")
if (".trace" in file): file = file[0:-6]

data = []
possibilities = []
pdata = {
    "s": [],
    "E": [],
    "b": [],
    "hits": [],
    "misses": [],
    "evics": [],
    "MR%": []
}
# (sMax, EMax, bMax) = map(int, input("settu inn hámarks gildi á s, E og b, aðgreint með bili: ").split(" "))



for i in range(1,13):
    for j in range(1,16):
        for u in range(3,15):
            comp = (2**i) * (2**j) * (2**u)
            if (comp == 2**15):
                if (not [u, 2**j, i] in possibilities):
                    possibilities.append([i,2**j,u])


for (i, p) in enumerate(possibilities):
    call("clear", shell=True)
    print(f"reiknuð {i:2} gildi")
    callstr = f'./csim-ref -s {p[0]} -E {p[1]} -b {p[2]} -t traces/{file}.trace'
    test = str(check_output(callstr, shell=True))
    
    test = test[2:-3].replace("\\n", " ").replace("miss ratio: ", "hitratio:").replace("  ", " ")
    output = test.split(" ")

    pdata["s"].append(p[0])
    pdata["E"].append(p[1])
    pdata["b"].append(p[2])
    pdata["hits"].append(float(output[0][5:]))
    pdata["misses"].append(float(output[1][7:]))
    pdata["evics"].append(float(output[2][10:]))
    pdata["MR%"].append(float(output[3][9:-1]))

call("clear", shell=True)

df = pd.DataFrame(pdata)
print(df.sort_values(["MR%"]))

df.to_csv(f"dumps/{file}_dump.csv")
