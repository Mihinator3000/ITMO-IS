#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str[100];//���������� ������ (������� ��������) ������ 100 ��������
    char ch;//���������� �������
    scanf("%s %c",&str,&ch);//���������� � ������� ������ � �������
    printf("%s\n%c",str,ch);//����� ������ � ������� � �������
    return 0;

}
