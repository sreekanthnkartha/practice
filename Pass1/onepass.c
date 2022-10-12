#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    FILE *input,*inter,*optab,*symtab;
    int locctr=0;
    char opcode[100],label[100],operand[100],symbol[100],nemonics[100],code[100];
    input=fopen("input.txt","r");
    optab=fopen("optab.txt","r");
    symtab=fopen("symbol.txt","w+");
    inter=fopen("inert.txt","w");
    
    fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        int start=strtol(operand,NULL,16);
        locctr=start;
        fprintf(inter,"\t%s    %s  %X",label,opcode,locctr);
        fscanf(input,"%s\t%s\t%s",label,opcode,operand);      
    }
    while (strcmp(opcode,"END")!=0)
    {
        fprintf(inter,"\n%X\t",locctr);
        if(strcmp(label,"-")!=0)
            fprintf(symtab,"%s\t%X\n",label,locctr);
        fseek(optab,SEEK_SET,0);
        fscanf(optab, "%s\t%s", code, nemonics);
        while(strcmp(code,"END")!=0)
        {
            if(strcmp(code,opcode)==0)
            {
                locctr+=3;
                break;
            }
            fscanf(optab, "%s\t%s", code, nemonics);
        }
        if(strcmp("WORD",opcode)==0)
            locctr+=3;
        else if (strcmp("RESW",opcode)==0)
            {
                int y=strtol(operand,NULL,16);
                locctr+=(3*y);
            }
        else if (strcmp("RESB",opcode)==0)
            {
                int y=strtol(operand,NULL,16);
                locctr+=(y);
            }
        else if (strcmp("BYTE",opcode)==0)
            {
                if(opcode[0]=='C')
                    locctr+=strlen(opcode)-3;
                else
                    locctr+=1;
            }
        fprintf(inter,"%s\t%s\t%s",label,opcode,operand);
        fscanf(input,"%s    %s  %s",label,opcode,operand); 

    }
    fprintf(inter,"\n%X\t%s\t%s\t%s",locctr,label,opcode,operand);
    fclose(input);
	fclose(inter);
	fclose(optab);
	fclose(symtab);
    return 0;
}
