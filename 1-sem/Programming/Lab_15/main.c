#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create(int argc, char *argv[])
{
    int i,j;
    char arc_name[100];
    strcpy(arc_name, argv[2]);
    int file_count = argc - 4;
    FILE *arc = fopen(arc_name, "w");
    fputc(file_count, arc);
    for (i = 0; i < file_count; i++)
    {
        int arg_len = strlen(argv[i + 4]);
        fputc(arg_len, arc);
        for (j = 0; j < arg_len; j++) fputc(argv[i + 4][j], arc);
        FILE *file = fopen(argv[i + 4], "r");
        fseek(file, 0, SEEK_END);
        int file_len = ftell(file);
        fseek(file, 0, SEEK_SET);
        fwrite(&file_len, sizeof(int), 1, arc);
        for (j = 0; j < file_len; j++)
        {
            char n = getc(file);
            fputc(n, arc);
        }
        fclose(file);
        remove(argv[i + 4]);
    }
    fclose(arc);
    return 0;
}

int extract(char *arc_name)
{
    int i,j;
    FILE *arc = fopen(arc_name, "r");
    int file_count = getc(arc);
    for (i = 0; i < file_count; i++)
    {
        int arg_len = getc(arc);
        char name[arg_len];
        for (j = 0; j < arg_len; j++)
        {
            name[j] = getc(arc);
        }
        name[arg_len] = '\0';
        FILE *file = fopen(name, "w");
        int file_len;
        fread(&file_len, sizeof(int), 1, arc);
        for (j = 0; j < file_len; j++)
        {
            char n = getc(arc);
            fputc(n, file);
        }
        fclose(file);
    }
    fclose(arc);
    remove(arc_name);
    return 0;
}

int list(char *arc_name)
{
    int i,j;
    FILE *arc = fopen(arc_name, "r");
    int file_count = getc(arc);
    for (i = 0; i < file_count; i++)
    {
        printf("%i) ", i + 1);
        int arg_len = getc(arc);
        for (j = 0; j < arg_len; j++) printf("%c", getc(arc));
        printf("\n");
        int file_len;
        fread(&file_len, sizeof(int), 1, arc);
        for (j = 0; j < file_len; j++) getc(arc);
    }
    fclose(arc);
    return 0;
}

int main(int argc, char *argv[])
{
    if (!strcmp(argv[3], "--create"))
    {
        create(argc, argv);
    }
    else if (!strcmp(argv[3], "--extract"))
    {
        extract(argv[2]);
    }
    else if (!strcmp(argv[3], "--list"))
    {
        list(argv[2]);
    }
	return 0;
}
