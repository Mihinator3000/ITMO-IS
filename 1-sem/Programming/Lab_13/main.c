#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show(char *filename, size_t s)
{
    FILE *file = fopen(filename, "r");
    char *data = (char *)malloc(sizeof(char) * s);
    fread(data, 1, s, file);
    int k = 10;
    while (data[k] != 0)
    {
        int i, j;
        for (i = 0; i < 4; i++)
        {
            printf("%c", data[k + i]);
        }
        printf(": ");
        int size = data[k + 7];
        k += 10;
        for (i = 1; i < size; i++)
        {
            printf("%c", data[k + i]);
        }
        printf("\n");
        k += size;
    }
    free(data);
    fclose(file);
}

void get(char *filename, size_t s, char *name)
{
    FILE *file = fopen(filename, "r");
    char *data = (char *)malloc(sizeof(char) * s);
    fread(data, 1, s, file);
    int k = 10;
    while (data[k] != 0)
    {
        int i,j;
        int size = data[k + 7];
        int boo = 1;
        for (i = 0; i < 4; i++)
        {
            if (data[k + i] != name[i]) boo = 0;
        }
        if (boo)
        {
            printf("%s: ", name);
            k += 10;
            for (i = 1; i < size; i++)
            {
                printf("%c", data[k + i]);
            }
            printf("\n");
            break;
        }
        else k += size + 10;
    }
    free(data);
    fclose(file);
}

void set(char *filename, size_t s, char *name, char *value)
{
    FILE *file = fopen(filename, "r+b");
    char *data = (char *)malloc(sizeof(char)* s);
    fread(data, 1, s, file);
    int k = 10;
    int length = strlen(value);
    while (data[k] != 0)
    {
        int i, j;
        int size = data[k + 7];
        int boo = 1;
        for (i = 0; i < 4; i++)
        {
            if (data[k + i] != name[i]) boo = 0;
        }
        if (boo)
        {
            k += 4;
            for (i = 0; i < 4; i++)
            {
                int pow = 1;
                for (j = 3; j > i; j--) pow *= 256;
                data[k + i] = (length/pow) % 256;
            }
            k += 6;
            fseek(file, 0, SEEK_SET);
            fwrite(data, 1, k, file);
            fwrite(value, 1, length, file);
            fwrite(&data[k + size], 1, s - size - k, file);
            break;
        }
        else k += size + 10;
    }
    free(data);
    fclose(file);
}

int main(int argc, char *argv[])
{
    int i = 1;
    while (i + 1 < argc)
    {
        char *filename = strpbrk(argv[i], "=") + 1;
        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            return 1;
        }
        else
        {
            size_t s;
            fseek(file, 0, SEEK_SET);
            if (file != NULL)
            {
                fseek(file, 0, SEEK_END);
                s = ftell(file);
            }
            else
            {
                s = 0;
                break;
            }
            close(file);
            if ((argv[i + 1][2] == 's') && (argv[i + 1][3] == 'h'))
            {
                show(filename, s);
            }
            else if ((argv[i + 1][2] == 's') && (argv[i + 1][3] == 'e'))
            {
                char *name = strpbrk(argv[i + 1], "=") + 1;
                char *value = strpbrk(argv[i + 2], "=");
                set(filename, s, name, value);
                i++;
            }
            else
            {
                char *name = strpbrk(argv[i + 1], "=") + 1;
                get(filename, s, name);
            }
            i += 2;
        }
    }
    return 0;
}
