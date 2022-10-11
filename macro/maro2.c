#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *finput, *fdeftab, *foutput, *fnamtab;

char label[50],
    opcode[50],
    operand[50],
    expandingMacroName[50],
    expandingMacroStart[10],
    expandingMacroEnd[10];

int expanding = 0;

void getline();
void processline();
void define();
void expand();


int main() {
    finput = fopen("input.txt", "r");
    fdeftab = fopen("deftab.txt", "w+");
    foutput = fopen("output.txt", "w");
    fnamtab = fopen("namtab.txt", "w+");

    expanding = 0;
    while(!feof(finput)) {
        getline();
        processline();
    }
}

void getline() {
    if(expanding == 1) {
        fscanf(fdeftab, "%s%s%s", label, opcode, operand);
    }else {
        fscanf(finput, "%s%s%s", label, opcode, operand);
    }
}

void processline() {
    char macroName[50] = "", macroStart[10] = "", macroEnd[10] = "";
    fseek(fnamtab, 0, SEEK_SET);
    int f = 0;
    while(!feof(fnamtab)) {
        fscanf(fnamtab, "%s%s%s", macroName, macroStart, macroEnd);
        if(strcmp(macroName, opcode) == 0) {
            f = 1;
            break;
        }
    }
    if(f) {
        strcpy(expandingMacroName, macroName);
        strcpy(expandingMacroStart, macroStart);
        strcpy(expandingMacroEnd, macroEnd);
        expand();
    }
    else if(strcmp(opcode, "MACRO") == 0) {
        define();
    }else {
        if(strcmp(opcode, "MEND") != 0) {
            fprintf(foutput, "%s %s %s\n", label, opcode, operand);
        }
    }
}

void expand() {
    expanding = 1;
    // printf("macro expadingin - \n");
    fseek(fdeftab, 0, atoi(expandingMacroStart));
    // printf("%d %d\n", atoi(expandingMacroStart), atoi(expandingMacroEnd));
    fscanf(fdeftab, "%s%s%s", label, opcode, operand);
    fprintf(foutput, ". %s %s\n", label, operand);
    int y = 0;
    while(strcmp(opcode, "MEND") != 0) {
        getline();
        processline();
    }
    expanding = 0;
}

void define() {
    fseek(fdeftab, 0, SEEK_END);
    fseek(fnamtab, 0, SEEK_END);
    fprintf(fnamtab, "%s %d ", label, ftell(fdeftab));
    char args[50][50];
    int argsCount=0, k=0;
    for(int i=0; i<strlen(operand); i++) {
        if((int)operand[i] == 44) {
            args[argsCount][k] = '\0';
            argsCount++;
            k = 0;
        }else {
            args[argsCount][k++] = operand[i];
        }
    }
    fprintf(fdeftab, "%s %s %s\n", label, opcode, operand);
    while(1) {
        getline();
        if(strcmp(opcode, "MEND") == 0) break;
        int i;
        for(i=0; i<=argsCount; i++) {
            if(strcmp(operand, args[i]) == 0) {
                break;
            }
        }
        fprintf(fdeftab, "%s %s ?%d\n", label, opcode, i+1);
    }
    fprintf(fdeftab, "- MEND -\n");
    fprintf(fnamtab, "%d\n", ftell(fdeftab));
}




===========================


input.txt



EX1 MACRO &A,&B
- LDA &A
- STA &B
- MEND -
EX2 MACRO &A,&B,&C
- LDA &A
- STA &C
- STA &B
- MEND -
SAMPLE START 1000
- EX1 N1,N2
N1 RESW 1
- EX2 N1,N2
N2 RESW 1
- END -




