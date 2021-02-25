#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum confectionery
{
    pie,
    cake,
    icecream,
    sweet
};

struct vertex
{
    double x;
    double y;
};

struct square
{
    struct vertex A;
    struct vertex B;
    struct vertex C;
    struct vertex D;
};

double side(const struct vertex *a, const struct vertex *b)
{
    double lenght = sqrt(pow(a -> x - b -> x, 2)+pow(a -> y - b -> y, 2));
    return lenght;
}

double perimeter(const struct square *t)
{
    double s = side(&t->A, &t->B);
    return s*4;
}

union
{
    int info;
    struct
    {
        int ready : 1;
        int low_toner: 1;
        int damaged_drum : 1;
        int no_paper : 1;
    }laser_printer;
}unity;

int main()
{
    enum confectionery s = sweet;
    printf("%d\n", s);

    struct vertex A = {0,0};
    struct vertex B = {3,5};
    struct vertex C = {8,2};
    struct vertex D = {5,-3};
    struct square sq = {A,B,C,D};
    printf("%lf\n", perimeter(&sq));

    scanf("%x", &unity.info);

    printf("%d ", -unity.laser_printer.ready);
    printf("%d ", -unity.laser_printer.low_toner);
    printf("%d ", -unity.laser_printer.damaged_drum);
    printf("%d ", -unity.laser_printer.no_paper);
    return 0;
}
