from math import*


class Vector(object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z


class Plane(object):
    def __init__(self, a, b, c, d):
        self.a = a
        self.b = b
        self.c = c
        self.d = d


def plane_create(a, b, c):
    b_a = Vector(b.x - a.x, b.y - a.y, b.z - a.z)
    c_a = Vector(c.x - a.x, c.y - a.y, c.z - a.z)
    p = Plane(0, 0, 0, 0)
    p.a = b_a.y * c_a.z - b_a.z * c_a.y
    p.b = b_a.z * c_a.x - b_a.x * c_a.z
    p.c = b_a.x * c_a.y - b_a.y * c_a.x
    p.d = -(a.x * p.a + a.y * p.b + a.z * p.c)
    k = length(Vector(p.a, p.b, p.c))
    p.a /= k
    p.b /= k
    p.c /= k
    p.d /= k
    return p


def intersection(o, v, p):
    point = Vector(0, 0, 0)
    numerator = p.a * v.x + p.b * v.y + p.c * v.z + p.d
    denominator = p.a * o.x + p.b * o.y + p.c * o.z
    if denominator == 0:
        if numerator == 0:
            return 1, point
        return 2, point
    f = - numerator / denominator
    point.x = v.x + f * o.x
    point.y = v.y + f * o.y
    point.z = v.z + f * o.z
    return 0, point


def reflection(a, p):
    n = Vector(p.a, p.b, p.c)
    projection = mult(a, n)
    codirectional = multnumb(n, projection)
    o = difference(a, multnumb(codirectional, 2))
    return o


def length(a):
    return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2))


def summ(a, b):
    c = Vector(a.x + b.x, a.y + b.y, a.z + b.z)
    return c


def difference(a, b):
    c = Vector(a.x - b.x, a.y - b.y, a.z - b.z)
    return c


def mult(a, b):
    c = a.x * b.x + a.y * b.y + a.z * b.z
    return c


def multnumb(a, b):
    c = Vector(a.x * b, a.y * b, a.z * b)
    return c


def _check(v, o, point):
    if (point.x - v.x) * o.x < 0 or (point.y - v.y) * o.y < 0 or (point.z - v.z) * o.z < 0:
        return 0
    if (point.x - v.x) * o.x == 0 and (point.y - v.y) * o.y == 0 and (point.z - v.z) * o.z == 0:
        return 0
    return 1

inp = open("input.txt")
outp = open("output.txt", "w")

a = Vector(0, 0, 0)
a.x, a.y, a.z = [float(i) for i in inp.readline().split()]

b = Vector(0, 0, 0)
b.x, b.y, b.z = [float(i) for i in inp.readline().split()]

c = Vector(0, 0, 0)
c.x, c.y, c.z = [float(i) for i in inp.readline().split()]

d = Vector(0, 0, 0)
d.x, d.y, d.z = [float(i) for i in inp.readline().split()]

orient = Vector(0, 0, 0)
orient.x, orient.y, orient.z = [float(i) for i in inp.readline().split()]

entry = Vector(0, 0, 0)
entry.x, entry.y, entry.z = [float(i) for i in inp.readline().split()]

energy = 0
energy = int(inp.readline())

n = 0
n = int(inp.readline())

mirrors = []
for i in range(n):
    mirrors.append([])
    for j in range(3):
        mirrors[i].append(Vector(0, 0, 0))
        mirrors[i][j].x, mirrors[i][j].y, mirrors[i][j].z = [float(k) for k in inp.readline().split()]

plane = []
for i in range(n):
    p = plane_create(mirrors[i][0], mirrors[i][1], mirrors[i][2])
    plane.append(p)

o = orient
v = entry


c1 = d
bc = difference(c, b)
d = summ(a, bc)
cc1 = difference(c1, c)
a1 = summ(a, cc1)
b1 = summ(b, cc1)
d1 = summ(d, cc1)

sides = []
sides.append(plane_create(a, b, c))
sides.append(plane_create(a1, b1, c1))
sides.append(plane_create(a, d, a1))
sides.append(plane_create(b, c, b1))
sides.append(plane_create(c, d, c1))
sides.append(plane_create(b, a, b1))

while 1:
    intersect = []
    new_plane = []
    for i in range(n):
        check, point = intersection(o, v, plane[i])
        if check == 0:
            if _check(v, o, point) == 1:
                intersect.append(point)
                new_plane.append(plane[i])
    l = []
    for i in range(len(intersect)):
        l.append(length(difference(v, intersect[i])))
    l_min_id = -1
    l_min = 0
    if len(l) > 0:
        l_min_id = 0
        l_min = l[0]
        for i in range(len(l)):
            if l_min > l[i]:
                l_min = l[i]
                l_min_id = i
    side_intersect = []
    for i in range(6):
        check, point = intersection(o, v, sides[i])
        if check == 0:
            if _check(v, o, point) == 1:
                side_intersect.append(point)
    side_l = []
    for i in range(len(side_intersect)):
        side_l.append(length(difference(v, side_intersect[i])))
    side_l_min_id = 0
    side_l_min = side_l[0]
    for i in range(len(side_l)):
        if side_l_min > side_l[i]:
            side_l_min = side_l[i]
            side_l_min_id = i
    if l_min_id != -1 and l_min < side_l_min:
        energy -= 1
        if energy == 0:
            print("0", file=outp)
            print(intersect[l_min_id].x,
                  intersect[l_min_id].y,
                  intersect[l_min_id].z,
                  file=outp)
            break
        o = reflection(o, new_plane[l_min_id])
        v = intersect[l_min_id]
    else:
        print("1", file=outp)
        print(energy, file=outp)
        print(side_intersect[side_l_min_id].x,
              side_intersect[side_l_min_id].y,
              side_intersect[side_l_min_id].z,
              file=outp)
        print(o.x, o.y, o.z, file=outp)
        break
inp.close()
outp.close()