#include "Pentagon.h"

struct point new_point(double x, double y) //Создание точки
{
    struct point d;
    d.x = x;
    d.y = y;
    return d;
};

struct pent new_pent(struct point a, struct point b, struct point c)
{
    //Создание пятиугольника
    struct pent p;
    p.a = a;
    p.b = b;
    p.c = c;
    return p;
};

double distance(struct point a, struct point b)
{
    //Функция подсчета расстояние между 2 точками
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double perimeter(struct pent p)
{
    //Функция подсчета периметра
    double a = distance(p.a, p.b);
    return 5 * a;
}
