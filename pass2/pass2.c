#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct textrec
{
    int index, length;
} rec[100];
struct objectcodes
{
    char a[100];
} oc[100];
int main(int argc, char const *argv[])
{
    FILE *inter, *output, *optab, *symtab;
    char locctr[100];
    char opcode[100], label[100], operand[100], symbol[100], sadd[100], nemonics[100], code[100], length_instr[100] = "18";
    optab = fopen("optab.txt", "r");
    symtab = fopen("symbol.txt", "r");
    inter = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    int j = 0, i = 0, maxlength = 0;
    rec[j].index = 0;
    rec[j].length = 0;
    j++;
    fscanf(inter,"%s\t%s\t%s\t%s",locctr, label, opcode, operand);
    int start = strtol(operand, NULL, 16);

    int length = strtol(length_instr, NULL, 16);
    fprintf(output, "H^%s^00%X^%X", label, start, length);
    fscanf(inter,"%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    // printf( "%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    while (strcmp(opcode, "END") != 0)
    {
        fseek(optab, SEEK_SET, 0);
        fscanf(optab, "%s\t%s", code, nemonics);
        while (!feof(optab))
        {

            if (strcmp(opcode, code) == 0)
            {
                fseek(symtab, SEEK_SET, 0);
                fscanf(symtab, "%s\t%s", symbol, sadd);
                while (!feof(symtab))
                {
                    // printf("hiii\n");
                    if (strcmp(symbol, operand) == 0)
                    {
                        strcpy(oc[i].a, nemonics);
                        strcat(oc[i].a, sadd);
                        maxlength += strlen(oc[i].a);
                        i++;
                        if (maxlength >= 60)
                        {
                            rec[j].index = i - 1;
                            rec[j].length = maxlength - strlen(oc[i - 1].a);
                            maxlength = strlen(oc[i - 1].a);
                            j++;
                        }
                        break;
                    }
                    fscanf(symtab, "%s\t%s", symbol, sadd);
                }
            }
            fscanf(optab, "%s\t%s", code, nemonics);
        }

        if (strcmp(opcode, "WORD") == 0)
        {
            char zero[6 - strlen(operand)];
            for (int ii = 0; ii < 6 - strlen(operand); ii++)
                zero[ii] = '0';
            strcpy(oc[i].a, zero);
            strcat(oc[i].a, operand);
            maxlength += 6;
            i++;
            if (maxlength >= 60)
            {
                rec[j].index = i - 1;
                rec[j].length = maxlength - 6;
                maxlength = 6;
                j++;
            }
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            int yy = 0;
        }
        fscanf(inter, "%X\t%s\t%s\t%s", locctr, label, opcode, operand);
    }
    if (maxlength < 60)
    {
        rec[j].index = i;
        rec[j].length = maxlength;
    }
    // printf("\n%i",maxlength);
    for (int k = 0; k < j; k++)
    {
        start += (rec[k].length / 2);
        fprintf(output, "\nT^%06X^%02X", start, rec[k + 1].length / 2);
        // printf("\n%i",rec[k + 1].length/2);
        for (int l = rec[k].index; l < rec[k + 1].index; l++)
        {
            // printf("fefr");
            fprintf(output, "^%s", oc[l].a);
        }
    }
    fprintf(output, "\nE^%06X", start);

    fclose(output);
    fclose(inter);
    fclose(optab);
    fclose(symtab);
    return 0;
}
