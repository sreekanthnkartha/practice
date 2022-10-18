#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct i{
char addr[20];
char lab[20];
char opc[20];
char ope[20];
}inp[100];
struct t{
    char ad[20];
    int len;
    char con[20][20];
    int co;
}txt[20];
main(){
    FILE *outp,*sym,*inter,*opt;
    sym=fopen("symbol.txt","r");
    inter=fopen("inter.txt","r");
    opt=fopen("optab.txt","r");
    outp=fopen("output.txt","w");
    int i=0,lines,f1=0,f2=0,to=0;
    char ol[20],oa[20],sl[20],sa[20];
    while(!feof(inter)){

        fscanf(inter,"%s%s%s%s",inp[i].addr,inp[i].lab,inp[i].opc,inp[i].ope);
        /*printf("\n%i %s %s %s\n",inp[i].addr,inp[i].lab,inp[i].opc,inp[i].ope);*/
        i++;
    }
    lines=i;
    fprintf(outp,"H\n");
    strcpy(txt[0].ad,inp[i].ope);
    txt[0].len=0;
    txt[0].co=0;
    for(i=1;i<lines;i++){
            fseek(opt,0,SEEK_SET);
            f1=0;
        while(!feof(opt)){
            fscanf(opt,"%s%s",ol,oa);
            if(strcmp(ol,inp[i].opc)==0){
                f1=1;
                break;
            }
        }
        if(f1==1){
            fseek(sym,0,SEEK_SET);
            f2=0;
            while(!feof(sym)){
                fscanf(sym,"%s%s",sl,sa);
                if(strcmp(sl,inp[i].ope)==0){
                    f2=1;
                    break;
                }
            }
            if(f2==1){
                sprintf(txt[to].con[txt[to].co],"%s%s",oa,sa);
                txt[to].co+=1;
                txt[to].len+=6;
            }
        }
        else if (strcmp(inp[i].opc,"WORD")==0){
            sprintf(txt[to].con[txt[to].co],"00000%s",inp[i].ope);
                txt[to].co+=1;
                txt[to].len+=6;
        }
        else{
            int ind=0;
            int as[20],j=0,k=0,legg;
            char dd[20];
            for(j=2,k=0;j<strlen(inp[i].ope)-1;j++,k++){
                as[k]=(int)inp[i].ope[j];
            }
            legg=k;
            for(j=0;j<legg;j++){
                ind+=sprintf(&dd[ind],"%x",as[j]);
            }
            sprintf(txt[to].con[txt[to].co],"%s",dd);
                txt[to].co+=1;
                txt[to].len+=legg;
        }
    }
    int j;
    for(i=0;i<=to;i++){
        printf("\nT^%s^%d",txt[i].ad,txt[i].len);
        for(j=0;j<txt[i].co;j++){
            printf("^%s",txt[i].con[j]);
        }
    }
}
