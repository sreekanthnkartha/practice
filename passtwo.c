#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct i{
int addr;
char lab[20];
char opc[20];
char ope[20];
}inp[100];
struct op{
    char opcode[20];
}opc[100];
struct te{
    int start;
    int leng;
    int addr;
    int end;
}txt[100];
main(){
    FILE *outp,*sym,*inter,*opt;
    sym=fopen("symbol.txt","r");
    inter=fopen("inter.txt","r");
    opt=fopen("optab.txt","r");
    outp=fopen("output.txt","w");
    int i=0,lines,co=0,length=10000,addr_o,addr_s,flag1,flag2,co_opc=0,co_txt=1;
    txt[0].start=0;
    char symb_o[20],symb_s[20];
    fscanf(inter,"%s %s %s %s",&inp[i].addr,inp[i].lab,inp[i].opc,inp[i].ope);
    i++;
    while(!feof(inter)){

        fscanf(inter,"%x %s %s %s",&inp[i].addr,inp[i].lab,inp[i].opc,inp[i].ope);
        /*printf("\n%i %s %s %s\n",inp[i].addr,inp[i].lab,inp[i].opc,inp[i].ope);*/
        i++;
    }
    lines=i;
    i=0;
    printf("%s",inp[0].opc);
    if(strcmp(inp[i].opc,"START")==0){

        fprintf(outp,"H^%s^%x^%x",inp[i].opc,inp[i].addr,length);
    }
    txt[0].addr=inp[i].addr;
    for(i=1;i<lines;i++){
            printf("\ndasdds %i",i);
       flag1=0;
       while(!feof(opt)){
            fscanf(opt,"%s %x",symb_o,&addr_o);
            if(strcmp(inp[i].opc,symb_o)==0){
                    flag1=1;
                if(strcmp(inp[i].ope,"-")!=0){
                    flag2=0;
                    while(!feof(sym)){
                            printf("\nope %s",inp[i].ope);
                        fscanf(sym,"%s %x",symb_s,&addr_s);
                        if(strcmp(symb_s,inp[i].ope)==0){
                            flag2=1;
                            /*strcpy(opc[co_opc].opcode,inp[i].opc);
                            strcat(opc[co_opc].opcode,ato)*/
                            sprintf(opc[co_opc].opcode,"%s%x",inp[i].opc,addr_s);/* sprintf*/

                            if(co+6>60){
                                    co_txt++;
                                txt[co_txt].start=co_opc;
                                txt[co_txt].addr=inp[i].addr;
                                txt[co_txt-1].leng=co;
                            co=0;
                            }
                            else{
                                co+=6;
                            }
                            co_opc++;
                        }
                    }
                    if(flag2==0){
                            printf("hhj");
                        exit(0);
                    }
                }
                else{
                    sprintf(opc[co_opc].opcode,"%s0000",inp[i].opc);
                    if(co+6>60){
                                    co_txt++;
                                txt[co_txt].start=co_opc;
                                txt[co_txt].addr=inp[i].addr;
                                txt[co_txt-1].leng=co;
                            co=0;
                            }
                            else{
                                co+=6;
                            }
                    co_opc++;
                }
            }
        }
        if(flag1==0){
            if(strcmp(inp[i].opc,"WORD")==0){
                int val=atoi(inp[i].ope),jj=0;
                char valc[20];
                sprintf(valc,"%x",val);
                char xe[4];
                while(jj<=(6-strlen(valc))){
                    xe[jj]='0';
                    jj++;
                    printf("fgfg");
                }
                sprintf(opc[co_opc].opcode,"%s%s",xe,valc);
                if(co+6>60){
                                    co_txt++;
                                txt[co_txt].start=co_opc;
                                txt[co_txt].addr=inp[i].addr;
                                txt[co_txt-1].leng=co;
                            co=0;
                            }
                            else{
                                co+=6;
                            }
                co_opc++;
            }
            else if(strcmp(inp[i].opc,"BYTE")==0){
                int val[20],jj=0,te,nn=0;
                if(strcmp(inp[i].opc[0],"C")==0){
                    for(jj=2;jj<(strlen(inp[i].opc)-1);jj++){
                        val[jj-2]=(int)inp[i].opc[jj];
                    }
                    te=jj;
                    for(jj=0;jj<te;jj++){
                        nn=sprintf(&opc[co_opc+nn].opcode[jj],"%x",val[jj]);
                    }
                    if(co+strlen(opc[co_opc].opcode)>60){
                                    co_txt++;
                                txt[co_txt].start=co_opc;
                                txt[co_txt].addr=inp[i].addr;
                                txt[co_txt-1].leng=co;
                            co=0;
                            }
                            else{
                                co+=strlen(opc[co_opc].opcode);
                            }
                co_opc++;
                }
                if(strcmp(inp[i].opc[0],"X")==0){
                    strncpy(opc[co_opc].opcode,&inp[i].opc[2],(strlen(inp[i].opc)-3));
                   if(co+strlen(opc[co_opc].opcode)>60){
                                    co_txt++;
                                txt[co_txt].start=co_opc;
                                txt[co_txt].addr=inp[i].addr;
                                txt[co_txt-1].leng=co;
                            co=0;
                            }
                            else{
                                co+=strlen(opc[co_opc].opcode);
                            }
                co_opc++;
                }
            }
        }
    }
    if(co_txt==0){
        txt[co_txt].leng=co;
        co_txt++;
    }
    for(i=0;i<co_txt-1;i++){
        fprintf(outp,"\nT^%i^%02x",txt[i].addr,txt[i].leng);
        int jj;
        for(jj=txt[i].start;jj<txt[i+1].start;jj++){
            fprintf(outp,"^%s",opc[jj].opcode);
        }
    }
    fprintf(outp,"\nT^%x^%02x",txt[i].addr,txt[i].leng);
    int jj;
        for(jj=txt[i].start;jj<co_opc;jj++){
            fprintf(outp,"^%s",opc[jj].opcode);
        }
    fprintf(outp,"\nE^%s",inp[0].ope);
}
