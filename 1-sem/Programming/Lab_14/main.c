#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int game(int **field, int height, int width)
{
    int **arr = (int**)malloc(height * sizeof(int*));
    int i,j;
    for (i = 0; i < height; i++)
    {
        arr[i] = (int*)malloc(width * sizeof(int));
        for (j = 0; j < width; j++)
        {
            arr[i][j] = field[i][j];
        }
    }
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            int count = 0;
            int k,m;
            for (k = i - 1; k < i + 2; k++)
            {
                for (m = j - 1; m < j + 2; m++)
                {
                    int t1, t2;
                    t1 = k;
                    t2 = m;
                    if (i == 0) t1 = width - 1;
                    if (j == 0) t2 = height - 1;
                    if (i == width - 1) t1 = 0;
                    if (j == height - 1) t2 = 0;
                    count += field[t1][t2];
                }
            }
            count -= field[i][j];
            if (field[i][j] == 0)
            {
                if (count == 3) arr[i][j] = 1;
            }
            else if (count < 2 || count > 3)
            {
                arr[i][j] = 0;
            }
        }
    }
    int changed = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (field[i][j] != arr[i][j])
            {
                field[i][j] = arr[i][j];
                changed = 1;
            }
        }
    }
    for (i = 0; i < height; i++)
    {
        free(arr[i]);
    }
    free(arr);
    if (changed) return 0;
    return 1;
}

void output(int **field, int height, int width, char *directory, char *input, int outpind, int iteration)
{
    FILE *image;
    FILE *imageout;
    image = fopen(input, "rb");
    char newinput[50];
    strcpy(newinput, directory);
    strcat(newinput, "\\");
    char buffer[50];
    strcat(newinput, itoa(iteration, buffer, 10));
    strcat(newinput, ".bmp");
    imageout = fopen(newinput, "wb");
    char c;
    int i, j;
    for (i = 0; i < outpind; i++)
    {
        c = fgetc(image);
        fputc(c, imageout);
    }
    for (i = 0; i < height; i++)
    {
        j = 0;
        c = 0;
        while (j < width)
        {
            c = c << 1;
            c += field[i][j];
            j++;
            if (j % 8 == 0)
            {
                fputc(c, imageout);
                c = 0;
            }
            else if (j == width)
            {
                int j1 = 8 - (j % 8);
                c = c << j1;
                j += j1;
                fputc(c, imageout);
            }
        }
    }
    fclose(image);
    fclose(imageout);
}

void load(int **field, FILE *image, int height, int width)
{
    int bit = 0;
    char c;
    int i,j;
    for (i = 0; i < height; i++)
    {
        int *line = (int*)malloc(width * sizeof(int));
        field[i] = line;
        bit = 0;
        while (bit < width)
        {
            c = fgetc(image);
            for (j = 0; j < 8; j++)
            {
                int n = (c >> (7 - j)) % 2;
                line[bit] = n;
                bit++;
                if (bit == width)
                {
                    bit += 7 - j;
                    break;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    char *input;
    char *directory;
    int iterations = 2147483647;
    int frequency = 1;
    int i,j;
    for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--input"))
        {
            input = argv[i + 1];
        }
        else if (!strcmp(argv[i], "--output"))
        {
            directory = argv[i + 1];
        }
        else if (!strcmp(argv[i], "--max_iter"))
        {
            iterations = atoi(argv[i + 1]);
        }
        else if (!strcmp(argv[i], "--dump_freq"))
        {
            frequency = atoi(argv[i + 1]);
        }
    }
    if ((input == NULL) || (directory == NULL)) return 1;
    FILE *image = fopen(input, "rb");
    mkdir(directory);
    char BITMAPFILEHEADER[14];
    char BITMAPINFORMATION[40];
    fread(BITMAPFILEHEADER, 1, 14, image);
    int outpind = BITMAPFILEHEADER[10] + BITMAPFILEHEADER[11] * 256 + BITMAPFILEHEADER[12] * 256 * 256 + BITMAPFILEHEADER[13] * 256 * 256 * 256;
    fread(BITMAPINFORMATION, 1, 40, image);
    int width = BITMAPINFORMATION[4] + BITMAPINFORMATION[5] * 256 + BITMAPINFORMATION[6] * 256 * 256 + BITMAPINFORMATION[7] * 256 * 256 * 256;
    int height = BITMAPINFORMATION[8] + BITMAPINFORMATION[9] * 256 + BITMAPINFORMATION[10] * 256 * 256 + BITMAPINFORMATION[11] * 256 * 256 * 256;
    char c;
    for (i = 54; i < outpind; i++)
    {
        c = fgetc(image);
    }
    int **field = (int**)malloc(height * sizeof(int*));
    load(field, image, height, width);
    fclose(image);
    for (i = 0; i < iterations; i++)
    {
        if (i % frequency == 0)
        {
            output(field, height, width, directory, input, outpind, i);
        }
        int exit = game(field, height, width);
        if (exit) break;
    }
    for (i = 0; i < height; i++)
    {
        free(field[i]);
    }
    free(field);
    return 0;
}
