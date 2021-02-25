#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    const float free = 499.0;
    float duration;
    float payment;
    float overlimit;
    float months = 0.0;
    //Ввод данных для 2 задания
    scanf("%f %f %f", &duration, &payment, &overlimit);
    if (payment/free < overlimit)
    {
        months = payment;
        if (free < duration)
        {
            months += (duration - free) * overlimit;
        }
        //Вывод стоимости оплаты
        printf("%f\n", months);
    }
    else
    {
        printf("The cost of a minute in the tariff is more than the cost of a minute over the limit\n");
    }
    int n;
    //Ввод числа для 4 задания
    scanf("%d", &n);
    int arr[n];
    int count = 0;
    arr[count] = 2;
    int i, j;
    for (i = 3; i <= n; i++)
    {
        int prime = 1;
        for (j = 0; j < count; j++)
        {
            if((i%arr[j]) == 0)
            {
                prime = 0;
                break;
            }
        }
        if(prime)
        {
            count++;
            arr[count] = i;
        }
    }
    for (i = 0; i <= count; i++)
    {
        //Вывод всех простых чисел до числа n
        printf("%d ", arr[i]);
    }
    return 0;
}
