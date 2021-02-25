#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char str1[100];
    char str2[100];
    int n;
    //Объявление и заполнение строк и n для задания 2
    scanf("%s %s %d",&str1,&str2,&n);
    printf("%s\n",strncat(str1,str2,n));
    //Вывод результата сложения 2 строк
    char str3[100];
    char ch;
    scanf("%s %c",&str3,&ch);
    //Объявление и заполнение строки для задания 7 и 9 и символа для задания 9
    printf("%d\n", strlen(str3));

    char *output;
    output = strrchr(str3, ch);
    //Нахождение последнего вхождения элемента в строке
    if (output!=NULL) printf("%d\n", output - str3 + 1);
    //Вывод последнего вхождения элемента в строку
    char str4[100];
    char str5[100];
    scanf("%s %s", &str4, &str5);
    //Объявление и заполнения строк для задания 11
    printf("%d\n",strspn(str4, str5));
    //Вывод длины отрезка 1 строки, содержащей символы только 2 строки
    char str6[100];
    char str7[100];
    scanf("%s %s", &str6, &str7);
    //Объявление и заполнения строк для задания 13
    char *symbols = strtok (str6, str7);
    //Разделение строки 1 символами 2 строки
    while(symbols != NULL)
    {
        //Пока остались лексемы
        printf("%s ",symbols);
        //Вывод лексемы
        symbols = strtok(NULL, str7);
        //Разделение строки
    }
    return 0;
}
