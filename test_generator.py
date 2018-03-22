import random as rd
R = 1 << 127
MIN = -R
MAX = R
T = 200
def normalized(x, R):
    return (x + R) % (R << 1) - R
def mod(a, b):
    return abs(a) % abs(b) * (1 if a * b >= 0 else -1)
def div(a, b):
    return abs(a) // abs(b) * (1 if a * b >= 0 else -1)

with open('testcases/test.in', 'w') as fin:
    with open('testcases/test.ans', 'w') as fout:
        print(T, file = fin)
        for i in range(T):
            a = rd.randint(MIN, MAX)
            b = rd.randint(MIN, MAX)
            print(a, b, file = fin)
            print(normalized(a + b, R), normalized(a - b, R), normalized(a * b, R), normalized(div(a, b), R), normalized(mod(a, b), R), file = fout)
