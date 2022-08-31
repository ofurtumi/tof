# |||||||||||||||||||||||||||||||||
# ||    __    sjomli.is    __    ||
# ||  _/  |_ __ __  _____ |__|   ||
# ||  \   __\  |  \/     \|  |   ||
# ||   |  | |  |  /  Y Y  \  |   ||
# ||   |__| |____/|__|_|__/__|   ||
# ||                             ||
# |||||||||||||||||||||||||||||||||

from math import floor, sqrt


def isprime(k):
    top = floor(sqrt(k))

    if k <= 2:
        return 0

    for i in range(3, top, 2):
        if k % i == 0:
            return 0

    return 1


n = 10000
cnt = 0
i = 3
a = 0
b = 0
while cnt < n:
    if isprime(i) and isprime(i + 2):
        print(f"{i} og {i+2}")
        cnt += 1

    i += 2
