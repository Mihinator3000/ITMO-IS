#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *new_file;
    new_file = fopen(argv[1], "r");
    //Открытие файла
    if (new_file == NULL)
    {
        //Проверка существования файла
        return 1;
    }
    int i = 1;
    while(1)
    {
        char s[100];
        char *str = fgets(s, 100, new_file);
        if (str == NULL) break;
        //Вывод четных строк файла
        if (i % 2 != 1) printf("%s\n", s);
        i++;
    }
    fclose(argv[1]);
    //Закрытие файла
    return 0;
}
