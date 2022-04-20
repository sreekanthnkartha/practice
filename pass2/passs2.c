#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Objectcode
{
    char a[100];
} oc[100];

struct record
{
    int sindex;
    int length;
} rec[100];

int main(int argc, char const *argv[])
{
    FILE *inter, *output, *optab, *symtab;
    optab = fopen("optab.txt", "r");
    symtab = fopen("symbol.txt", "r");
    inter = fopen("input.txt", "r");
    output = fopen("output1.txt", "w");

    char label[100], opcode[100], operand[100], code[100], nmonics[100], sym[100], symadd[100],locctr[100];
    char length_instr[100] = "18";
    int i = 0, j = 1, maxlength = 0;
    rec[0].sindex = 0;
    rec[0].sindex = 0;
    fscanf(inter, "%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    int start = strtol(operand, NULL, 16);
    int length = strtol(length_instr, NULL, 16);
    fprintf(output, "H^%s^00%04X^%X", label, start, length);
    fscanf(inter, "%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    while (strcmp(opcode, "END") != 0)
    {

        fseek(optab, SEEK_SET, 0);
        fscanf(optab, "%s\t%s", code, nmonics);
        while (!feof(optab))
        {
            if (strcmp(code, opcode) == 0)
            {
                fseek(symtab, SEEK_SET, 0);
                fscanf(symtab, "%s\t%s", sym, symadd);
                while (!feof(symtab))
                {
                    if (strcmp(operand, sym) == 0)
                    {
                        strcpy(oc[i].a, nmonics);
                        strcat(oc[i].a, symadd);
                        i++;
                        maxlength += strlen(oc[i - 1].a);
                        if (maxlength >= 60)
                        {
                            rec[j].sindex = i - 1;
                            rec[j].length = maxlength - strlen(oc[i - 1].a);
                            maxlength = strlen(oc[i - 1].a);
                            j++;
                        }
                    }
                    fscanf(symtab, "%s\t%s", sym, symadd);
                }
            }
            fscanf(optab, "%s\t%s", code, nmonics);
        }
        if (strcmp("WORD", opcode) == 0)
        {
            char zero[6 - strlen(operand)];
            for (int ii = 0; ii < 6 - strlen(operand); ii++)
                zero[ii] = '0';
            strcpy(oc[i].a, zero);
            strcat(oc[i].a, operand);
            i++;
            maxlength += strlen(oc[i - 1].a);
            if (maxlength >= 60)
            {
                rec[j].sindex = i - 1;
                rec[j].length = maxlength - strlen(oc[i - 1].a);
                maxlength = strlen(oc[i - 1].a);
                j++;
            }
        }
        if (strcmp("BYTE", opcode) == 0)
        {
            int ry=0;
            // thane code cheyy
        }

        fscanf(inter, "%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    }
    if(maxlength<60)
    {
        rec[j].sindex=i;
        rec[j].length=maxlength;
    }
    int temp=start;
    for(int k=0;k<j;k++)
    printf("\nT^00%04X^%d",start,rec[k+1].length);
    for(int k=0;k<j;k++)
    {
        start+=(rec[k].length/2);
        fprintf(output,"\nT^00%04X^%02X",start,rec[k+1].length/2);
        for(int kk=rec[k].sindex;kk<rec[k+1].sindex;kk++)
        {
            fprintf(output,"^%s",oc[kk].a);
        }
    }
    fprintf(output, "\nE^%06X", temp);

    fclose(output);
    fclose(inter);
    fclose(optab);
    fclose(symtab);
    return 0;
}
