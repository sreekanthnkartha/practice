#include <stdio.h>
#include <string.h>
#include <Stdlib.h>
struct o{
 char ope[10];
}opbl[100];
struct t{
 int sta;
 int leng;
}textrec[10];
main(){
    FILE *op,*ip,*ou,*sy;
    char opc[10],lab[10],ope[10],op_op[10],ad_op[10],sy_sy[10],ad_sy[10];
    int sta,co=0,len=18,adr,opblind=0,textrecind=1,flag=0,flagop=0;
    ou=fopen("output.txt","w+");
    sy=fopen("symbol.txt","r");
    ip=fopen("input1.txt","r");
    op=fopen("optabl.txt","r");
    textrec[0].sta=0;
    textrec[0].leng=0;
    fscanf(ip,"%i\t%s\t%s\t%s",adr,lab,opc,ope);
    if(strcmp(opc,"START")==0){
        sta=strtol(ope,NULL,10);
    }
    fprintf(ou,"H^%s^%i^%i\n",lab,sta,len);
    co=sta;

    fscanf(ip,"%i\t%s\t%s\t%s",adr,lab,opc,ope);
    while(strcmp(opc,"END")!=0){
        fscanf(op,"%s\t%s",op_op,ad_op);
        while(!feof(op)){
            if(strcmp(op_op,opc)==0){
                if(strcmp(ope,"-")!=0){
                        flag=0;
                    fscanf(sy,"%s\t%s",sy_sy,ad_sy);
                    while(!feof(sy)){
                        if(strcmp(sy_sy,ope)==0){
                            char ass[100];
                            strcpy(ass,ad_op);
                            strcat(ass,ad_sy);
                            strcpy(opbl[opblind].ope,ass);
                            co+=strlen(ass);
                            if(co>=60){
                                textrec[textrecind].leng=co-strlen(ass);
                                textrec[textrecind].sta=opblind;
                                co=strlen(ass);
                            }
                            opblind++;
                            flag=1;
                        }
                        fscanf(sy,"%s\t%s",sy_sy,ad_sy);
                    }
                    fseek(sy,SEEK_SET,0);
                    if(flag==0){
                        char ass[100];
                        strcpy(ass,opc);
                        strcat(ass,"0000");
                        strcpy(opbl[opblind].ope,ass);
                            co+=strlen(ass);
                            if(co>=60){
                                textrec[textrecind].leng=co-strlen(ass);
                                textrec[textrecind].sta=opblind;
                                co=strlen(ass);
                            }
                            opblind++;
                            flag=1;
                    }
                }
            }
            fscanf(op,"%s\t%s",op_op,ad_op);
        }
        fseek(op,SEEK_SET,0);
        if(strcmp(opc,"BYTE")==0){       /* import */
            char ass[100];
            int i ,index=0,asci[100],coas=0;
            for(i=2;i<strlen(ope)-1;i++){
                asci[coas++]=(int)ope[i];
            }
            for(i=0;i<coas;i++){
                index+=sprintf(&ass[index],"%x",asci[i]);
            }
            strcpy(opbl[opblind].ope,ass);
            co+=strlen(ass);
            if(co>=60){
                    textrec[textrecind].leng=co-strlen(ass);
                    textrec[textrecind].sta=opblind;
                    co=strlen(ass);
            }
            opblind++;
        }
        else if (strcmp(opc,"WORD")==0){
            char ass[100];

            int noze=6-strlen(ope),i;
            for(i=0;i<noze;i++){
                ass[i]='0';
            }
            strcat(ass,ope);
            co+=strlen(ass);
            if(co>=60){
                    textrec[textrecind].leng=co-strlen(ass);
                    textrec[textrecind].sta=opblind;
                    co=strlen(ass);
            }
            opblind++;
        }
        fscanf(ip,"%i\t%s\t%s\t%s",adr,lab,opc,ope);
    }
    if(co<60){
        textrec[textrecind].leng=co;
        textrec[textrecind++].sta=opblind;
    }
    int a = strtol(sta, NULL, 16);
    int i,j;
    for(i=0;i<textrecind-1;i++){
        a=a+(textrec[i].leng/2);
        fprintf(ou, "T^%02X^", a);
        fprintf(ou, "%X^", textrec[i + 1].leng / 2);
        for (j = textrec[i].sta; j < textrec[i + 1].sta; j++)
        {
            fprintf(ou, "%s^", opbl[j].ope);
        }
        fprintf(ou, "\n");
    }
    fprintf(ou, "E^00%s", sta);
}
