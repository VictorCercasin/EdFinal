#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "retangulo.h"

typedef struct retangulo
{
    char corp[100], corb[100];
    char id[100], sw[100];
    double w, h;
    ponto coord;
} objRet;

retangulo montaRetangulo(char *id,char *sw ,double w,double h, double x, double y, char *corb, char *corp){

        objRet *ret;
        ret = (objRet *) calloc (1, sizeof(objRet));

        if(corp!=NULL && corb != NULL){
                if(corp[strlen(corp)-1]=='\n'){
                        corp[strlen(corp)-1]='\0'; // Para tirar o '\n'
                }
                strcpy(ret->corp, corp);
                strcpy(ret->corb, corb);
        }

        strcpy(ret->id, id);
        strcpy(ret->sw, sw);

        ponto pt = montaPonto(x,y);

        ret->coord = pt;

        ret->w = w;
        ret->h = h;
        
        return ret;
}

double retornaRet_X(retangulo r){
        objRet *ret = (objRet *) r;
        return retornaPonto_X(ret->coord);
}

double retornaRet_Y(retangulo r){
        objRet *ret = (objRet *) r;
        return retornaPonto_Y(ret->coord);
}

double retornaRet_W(retangulo r){
        objRet *ret = (objRet *) r;
        return ret->w;
}

double retornaRet_H(retangulo r){
        objRet *ret = (objRet *) r;
        return ret->h;
}

char *retornaRet_Id(retangulo r){
        objRet *ret = (objRet *) r;
        return ret->id;
}

char *retornaRet_SW(retangulo r){
        objRet *ret = (objRet *) r;
        return ret->sw;
}

char *retornaRet_Corp(retangulo r){
        objRet *ret = (objRet *) r;
        return ret->corp;
}

char *retornaRet_Corb(retangulo r){
        objRet *ret = (objRet *) r;
        return ret->corb;
}

void removeRetangulo(retangulo r){
        objRet *ret = (objRet *) r;
        free(ret->coord);
        free(ret);
}

ponto retornaRetCoord(retangulo r){
        objRet *ret = (objRet *) r;
        return ret->coord;
}

void alteraRet_Corb(retangulo r, char *corb){
        objRet *ret = (objRet *) r;
        strcpy(ret->corb,corb);

        return;
}

void alteraRet_Corp(retangulo r, char *corp){
        objRet *ret = (objRet *) r;
        strcpy(ret->corp,corp);

        return;
}