#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str[100];//Объявление строки (массива символов) длиной 100 символов
    char ch;//Объявление символа
    scanf("%s %c",&str,&ch);//Считывание с консоли строки и символа
    printf("%s\n%c",str,ch);//Вывод строки и символа в консоль
    return 0;

}
