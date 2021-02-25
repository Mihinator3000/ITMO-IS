#include <stdio.h>
#include "Pentagon.h"

int main()
{
    struct point a[3];
    int i;
    for (i = 0; i < 3; i++)
    {
        scanf("%lf %lf", &a[i].x, &a[i].y);
    }
    struct pent p = new_pent(a[0], a[1], a[2]);
    printf("%lf", perimeter(p));
    return 0;
}
