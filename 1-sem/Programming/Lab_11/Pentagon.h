#ifndef PENTAGON_H_INCLUDED
#define PENTAGON_H_INCLUDED
struct point
{
    double x;
    double y;
};

struct pent
{
    struct point a;
    struct point b;
    struct point c;
};

struct point new_point(double, double);
struct pent new_pent(struct point, struct point, struct point);
double distance(struct point, struct point);
double perimeter(struct pent);

#endif // PENTAGON_H_INCLUDED
