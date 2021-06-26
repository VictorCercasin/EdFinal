#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ponto.h"

typedef struct stPonto
{
    double x, y;
} objPonto;

ponto montaPonto(double x, double y){

        objPonto *p;
        p = (objPonto *) malloc (sizeof(objPonto));

        p->x = x;
        p->y = y;
        
        return p;
}

ponto *criaArrayPontos(int tamanho){
        ponto *array = (ponto*) malloc (tamanho * sizeof(ponto));
        return array;
}

void alteraPonto_X(ponto p, double n){
        objPonto *pnt = (objPonto *) p;
        pnt->x = n;
}

void alteraPonto_Y(ponto p, double n){
        objPonto *pnt = (objPonto *) p;
        pnt->y = n;
}

double retornaPonto_X(ponto p){
        objPonto *pnt = (objPonto *) p;
        return pnt->x;
}

double retornaPonto_Y(ponto p){
        objPonto *pnt = (objPonto *) p;
        return pnt->y;
}

char *retornaChaveExtra(){
        return "none";
}

void removePonto(ponto p){
        objPonto *pnt = (objPonto *) p;
        free(pnt);
}