#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "regiao.h"

typedef struct regiao
{ 
    double w, h, d;
    ponto coord;
} objReg;

regiao montaRegiao(double x,double y, double w, double h, double d){

        objReg *reg;
        reg = (objReg *) calloc (1, sizeof(objReg));

        ponto pt = montaPonto(x,y);

        reg->coord = pt;
        reg->w = w;
        reg->h = h;
        reg->d = d;

        return reg;
}

double retornaReg_X(regiao r){
        objReg *reg = (objReg *) r;
        return retornaPonto_X(reg->coord);
}

double retornaReg_Y(regiao r){
        objReg *reg = (objReg *) r;
        return retornaPonto_Y(reg->coord);;
}

double retornaReg_W(regiao r){
        objReg *reg = (objReg *) r;
        return reg->w;
}

double retornaReg_H(regiao r){
        objReg *reg = (objReg *) r;
        return reg->h;
}

double retornaReg_D(regiao r){
        objReg *reg = (objReg *) r;
        return reg->d;
}

ponto retornaRegiaoCoord(regiao r){
        objReg *reg = (objReg *) r;
        return reg->coord;
}

void removeRegiao(regiao r){
        objReg *reg = (objReg *) r;
        free(reg->coord);
        free(reg);
}