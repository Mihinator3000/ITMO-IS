#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int main()
{
    int const size = 4;
    int arr1[size];
    int *pointer = arr1;
    arr1[0] = 50;
    arr1[1] = 40;
    arr1[2] = 30;
    arr1[3] = 20;
    for(int i = 0; i < size; i++)
    {
        printf("%d %d\n",i,*(pointer+i));
    }
    printf("\n");
    int *arr2;  // указатель на массив
    arr2 = (int*)malloc(size * sizeof(int));
    arr2[0] = 50;
    arr2[1] = 40;
    arr2[2] = 30;
    arr2[3] = 20;
    for (int i = 0; i < size; i++)
    {
        printf("%d %d\n",i , arr2[i]);
    }
    free(arr2);
    return 0;
}
