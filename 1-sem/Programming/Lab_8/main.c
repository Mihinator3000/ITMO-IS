#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char str1[100];
    char str2[100];
    int n;
    //���������� � ���������� ����� � n ��� ������� 2
    scanf("%s %s %d",&str1,&str2,&n);
    printf("%s\n",strncat(str1,str2,n));
    //����� ���������� �������� 2 �����
    char str3[100];
    char ch;
    scanf("%s %c",&str3,&ch);
    //���������� � ���������� ������ ��� ������� 7 � 9 � ������� ��� ������� 9
    printf("%d\n", strlen(str3));

    char *output;
    output = strrchr(str3, ch);
    //���������� ���������� ��������� �������� � ������
    if (output!=NULL) printf("%d\n", output - str3 + 1);
    //����� ���������� ��������� �������� � ������
    char str4[100];
    char str5[100];
    scanf("%s %s", &str4, &str5);
    //���������� � ���������� ����� ��� ������� 11
    printf("%d\n",strspn(str4, str5));
    //����� ����� ������� 1 ������, ���������� ������� ������ 2 ������
    char str6[100];
    char str7[100];
    scanf("%s %s", &str6, &str7);
    //���������� � ���������� ����� ��� ������� 13
    char *symbols = strtok (str6, str7);
    //���������� ������ 1 ��������� 2 ������
    while(symbols != NULL)
    {
        //���� �������� �������
        printf("%s ",symbols);
        //����� �������
        symbols = strtok(NULL, str7);
        //���������� ������
    }
    return 0;
}
