def matrix(n, m, line):
    A = []
    counter = 0
    for i in range(n):
        A.append([])
        for j in range(m):
            A[i].append(float(line[counter]))
            counter += 1
    return A

def sum(A, nA, mA, B, nB, mB):
    if nA != nB: return None
    if mA != mB: return None
    C = []
    for i in range(nA):
        C.append([])
        for j in range(mA):
            C[i].append(A[i][j] + B[i][j])
    return C

def multN(A, n, m, number):
    for i in range(n):
        for j in range(m):
            A[i][j] *= number
    return A

def multM(A, nA, mA, B, nB, mB):
    if mA != nB: return None
    C = []
    for i in range(nA):
        C.append([])
        for j in range(mB):
            C[i].append(0)
    for i in range(nA):
        for j in range(mB):
            for k in range(nB):
                C[i][j] += A[i][k] * B[k][j]
    return C

def tran(A, n, m):
    B = []
    for i in range(m):
        B.append([])
        for j in range(n):
            B[i].append(A[j][i])
    return B

inp = open("input.txt")
outp = open("output.txt", "w")

alpha, beta = [float(i) for i in inp.readline().split(" ")]

nA, mA = [int(i) for i in inp.readline().split(" ")]
line = inp.readline().split(" ")
A = matrix(nA, mA, line)

nB, mB = [int(i) for i in inp.readline().split(" ")]
line = inp.readline().split(" ")
B = matrix(nB, mB, line)

nC, mC = [int(i) for i in inp.readline().split(" ")]
line = inp.readline().split(" ")
C = matrix(nC, mC, line)

nD, mD = [int(i) for i in inp.readline().split(" ")]
line = inp.readline().split(" ")
D = matrix(nD, mD, line)

nF, mF = [int(i) for i in inp.readline().split(" ")]
line = inp.readline().split(" ")
F = matrix(nF, mF, line)

possible = 1
alpha_A = multN(A, nA, mA, alpha)
beta_B = multN(B, nB, mB, beta)
beta_B_T = tran(beta_B, len(beta_B), len(beta_B[0]))
S = sum(alpha_A, len(alpha_A), len(alpha_A[0]), beta_B_T, len(beta_B_T), len(beta_B_T[0]))
if S == None: possible = 0
else:
    T = tran(S, len(S), len(S[0]))
    C_T = multM(C, nC, mC, T, len(T), len(T[0]))
    if C_T == None: possible = 0
    else:
        C_T_D = multM(C_T, len(C_T), len(C_T[0]), D, nD, mD)
        if C_T_D == None: possible = 0
        else:
            _F = multN(F, nF, mF, -1)
            X = sum(C_T_D, len(C_T_D), len(C_T_D[0]), _F, len(_F), len(_F[0]))
            if X == None: possible = 0
print(possible, file=outp)
if possible == 1:
    print(len(X), len(X[0]), file=outp)
    for i in range(len(X)):
        for j in range(len(X[i])):
            print(X[i][j], file=outp)
inp.close()
outp.close()