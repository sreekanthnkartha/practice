#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Driver code

int main(int argc, char const *argv[])
{
    FILE *input;
    for(int yy=0;yy<10;yy++){

        printf("");
    }
    char a[100], b[100], c[100], d[100], l[100];
    input = fopen("input.txt", "r");
    fscanf(input, "%s", l);
    int co = 0, aa = 0, bb = 0, cc = 0, dd = 0;
    for (int i = 0; i < strlen(l); i++)
    {
        if (l[i] == '^')
        {
            co++;
            continue;
        }
        if (co == 1)
        {
            a[aa++] = l[i];
        }
        if (co == 2)
        {
            b[bb++] = l[i];
        }
        if (co == 3)
        {
            c[cc++] = l[i];
        }
    }
    a[aa] = '\0';
    b[bb] = '\0';
    c[cc] = '\0';
    do
    {
        fscanf(input, "%s", l);
        if (l[0] == 'T')
        {
            // printf("%s 2 2 2\n",l);
            co=0;
            dd = 0;
            for (int i = 0; i < strlen(l); i++)
            {
                if (l[i] == '^')
                {
                    co++;
                    continue;
                }
                if (co == 1)
                {
                    d[dd++] = l[i];
                    // printf("%c 2 2 2\n",l[i]);
                }
                if (co == 3)
                {
                    break;
                }
            }
            d[dd] = '\0';
            int k = 12;
            int stsdd = strtol(d, NULL, 16);
            for (int i = k; i < strlen(l);)
            {
                if (l[i] != '^')
                {
                    printf("%X\t%c%c\n", stsdd, l[i], l[i + 1]);
                    i+=2;
                }
                else
                    i++;
            }
        }

    } while (!feof(input));

    return 0;
}

// END
