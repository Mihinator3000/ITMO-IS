#include <stdio.h>
#include <stdlib.h>
int main()
{
    int arr[7]={90,76,54,23,56,12,48};
    //���������� ������� � ��� ����������
    for(int i = 0; i < 7; i++)
    {
        printf("%d %d\n", i, arr[i]);
        //����� ������ �������� ������� � �������� �������
    }
    int m1[2][2]=
    {
        {2,5},
        {2,2}
    };
    //���������� � ���������� ������ �������
    int m2[2][2]=
    {
        {1,2},
        {0,1}
    };
    //���������� � ���������� ������ �������
    int m3[2][2]=
    {
        {0,0},
        {0,0}
    };
    //���������� ���������� �������
    int i,j,k;
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            for(k = 0; k < 2; k++)
            {
                m3[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            printf("%d ",m3[i][j]);
        }
        printf("\n");
    }
    return 0;
}
