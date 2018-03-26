import random as rd
R = 1 << 127
MIN = -R
MAX = R
T = 1000
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
            if i % 100 == 1:
                R >>= 10
            a = rd.randint(-R, R)
            b = rd.randint(-R, R)
            print(a, b, file = fin)
            print(normalized(a + b, MAX), normalized(a - b, MAX), normalized(a * b, MAX), normalized(div(a, b), MAX), normalized(mod(a, b), MAX), file = fout)
