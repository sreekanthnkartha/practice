#include <stdio.h>
#include <string.h>
#include <Stdlib.h>
main(){
FILE *op,*ip,*ou,*sy;
char opc[10],lab[10],ope[10],op_op[10],ad_op[10],flag=0;
int sta,loc=0;
ou=fopen("ou.txt","w+");
sy=fopen("sym.txt","w+");
ip=fopen("input.txt","r");
op=fopen("op.txt","r");
fscanf(ip,"%s%s%s",lab,opc,ope);
if(strcmp(opc,"START")==0){
    sta=strtol(ope,NULL,16);
    loc=sta;
}
fprintf(ou,"\t%s\t%s\t%s",lab,opc,ope);
fscanf(ip,"%s\t%s\t%s",lab,opc,ope);
while(strcmp(opc,"END")!=0){

    fprintf(ou,"\n%x\t",loc);
    flag=0;
    if(strcmp(lab,"-")!=0){
        printf("fdfdf %s %i",lab,loc);
        fprintf(sy,"\n%s\t%x",lab,loc);
    }
    fscanf(op,"%s\t%s",op_op,ad_op);
    fscanf(op,"%s\t%s",op_op,ad_op);
    while(!feof(op)){
        printf("ff");
       if(strcmp(op_op,opc)==0){
        flag=1;
        loc+=3;
        break;
       }
       fscanf(op,"%s\t%s",op_op,ad_op);
    }
    printf("\n %s %s %s",lab,opc,ope);
    if(flag==0){
            printf("\n %s %i",lab,loc);
        if(strcmp(opc,"WORD")==0){
            loc+=3;
        }
        else if(strcmp(opc,"RESW")==0){
            loc+=3*(ope);
        }
        else if(strcmp(opc,"BYTE")==0){
            if(ope[0]=='X'){
                loc=loc+((strlen(ope)-3)/2);
            }
            else{
                loc+=strlen(ope)-3;
            }
        }
        else if(strcmp(opc,"RESB")==0){
            loc+=(ope);
        }
        else{
            printf("Error");
        }
    }
    fprintf(ou,"%s\t%s\t%s",lab,opc,ope);
    fscanf(ip,"%s%s%s",lab,opc,ope);
}
printf("\n\n%x",(loc-sta));
}
