#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point
{
    //��������� �����
    double x,y;
};

double distance(struct point a, struct point b)
{
    //������� �� ������� ����������
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double** points(struct point a[100], int n)
{
    //������� ������������ ������ ����������
    double **arr = (double **)malloc(n * sizeof(double *));
    int i,j;
    for(i = 0; i < n; i++)
    {
        arr[i] = (double *)malloc(n*sizeof(double));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            //������� ���������� �� ����� i �� ����� j
            arr[i][j] = distance(a[i], a[j]);
        }
    }
    return arr;
}

int sum(int n)
{
    //������� ������������ ����� ���� �����
    int s = 0;
    while (n != 0)
    {
        s += n%10;
        n /= 10;
    }
    return s;
}

int main()
{
    int n, i, j;
    scanf("%d", &n);
    struct point a[n];
    for (i = 0; i < n; i++)
    {
        scanf("%lf %lf" , &a[i].x, &a[i].y);
    }
    double** arr = points(a, n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j)
            {
                printf("%lf " , arr[i][j]);
                //����� 2 �������
            }
        }
        printf("\n");
    }
    for(i = 0; i < n; i++)
    {
        free(arr[i]);
    }
    free(arr);
    scanf("%d", &n);
    int output_4 = sum(n);
    printf("%d", output_4);
    //����� 4 �������
    return 0;
}
