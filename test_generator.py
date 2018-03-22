import random as rd
R = 1 << 128
MIN = -R
MAX = R
T = 100

with open('testcases/test.in', 'w') as fin:
    with open('testcases/test.ans', 'w') as fout:
        for i in range(T):
            a = rd.randint(MIN, MAX)
            b = rd.randint(MIN, MAX)
            print(a, b, file = fin)
            print((a + b) % R, (a - b) % R, (a * b) % R, (a // b) % R, file = fout)
