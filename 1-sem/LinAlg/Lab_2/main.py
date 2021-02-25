from math import*


class Vector(object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z


def mult(a, b):
    c = Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x)
    return c


def length(a):
    return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2))


def signum(a, b):
    return 1 if a.x * b.y - a.y * b.x > 0 else -1


def angle(a, b):
    sin = signum(a, b) * length(mult(a, b)) / (length(a) * length(b))
    return degrees(asin(sin))


def signum_add(a, b):
    if a.x * b.y < 0 or a.y * b.x > 0: return -1
    if a.x * b.y > 0 or a.y * b.x < 0: return 1
    return 0


def angle_add(a, b):
    return degrees(acos((a.x * b.x + a.y * b.y + a.z * b.z) / (length(a) * length(b))))


inp = open("input.txt")
outp = open("output.txt", "w")

u = Vector(0, 0, 0)
u.x, u.y = [float(i) for i in inp.readline().split()]

a = Vector(0, 0, 0)
a.x, a.y = [float(i) for i in inp.readline().split()]

m = Vector(0, 0, 1)
m.x, m.y = [float(i) for i in inp.readline().split()]

w = Vector(0, 0, 0)
w.x, w.y = [float(i) for i in inp.readline().split()]

pos = Vector(u.x - w.x, u.y - w.y, u.z - w.z)
n = Vector(0, 0, 1)
s = mult(n, a)
phi = angle(pos, a)
beta = angle(s, pos)
if beta > -60 and beta < 60:
    if phi > 0:
        print(1, file=outp)
    else:
        print(-1, file=outp)
else:
    print(0, file=outp)
print(round(beta, 2), file=outp)

gamma = signum_add(a, m) * angle_add(n, m)
print(round(gamma, 2), file=outp)
print("Arriva", file=outp)
inp.close()
outp.close()