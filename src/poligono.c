#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "poligono.h"

typedef struct poligono
{
    ponto *arrayPontos;
    int tam;
    char cor[100];
} objPol;

poligono montaPoligono(ponto *array, int tam){

    objPol *pol;
    pol = (objPol *) calloc (1, sizeof(objPol));
        
    pol->arrayPontos = array;
    pol->tam = tam;

    return pol;
}

void addCor(poligono p, char *cor){
    objPol *pol = (objPol*) p;
    strcpy(pol->cor,cor);   
}

ponto encontrarCentroide(poligono poly, long double area){

    objPol *pol = (objPol*) poly;
    ponto *array = pol->arrayPontos;
    double cx = 0,cy = 0;

    for(int i=0;i < pol->tam; i++){

        if( i == pol->tam-1){
            cx = (retornaPonto_X(array[i]) + retornaPonto_X(array[0])) * ((retornaPonto_X(array[i]) * retornaPonto_Y(array[0])) - (retornaPonto_X(array[0]) * retornaPonto_Y(array[i]))) + cx;
            cy = (retornaPonto_Y(array[i]) + retornaPonto_Y(array[0])) * (retornaPonto_X(array[i]) * retornaPonto_Y(array[0]) - retornaPonto_X(array[0]) * retornaPonto_Y(array[i])) + cy;
        }

        else{
            cx = (retornaPonto_X(array[i]) + retornaPonto_X(array[i+1])) * ((retornaPonto_X(array[i]) * retornaPonto_Y(array[i+1])) - (retornaPonto_X(array[i+1]) * retornaPonto_Y(array[i]))) + cx;
            cy = (retornaPonto_Y(array[i]) + retornaPonto_Y(array[i+1])) * (retornaPonto_X(array[i]) * retornaPonto_Y(array[i+1]) - retornaPonto_X(array[i+1]) * retornaPonto_Y(array[i])) + cy;
        }
        
    }

    cx = (1/(6*area)) * cx * (-1);
    cy = (1/(6*area)) * cy * (-1);

    ponto pnt = montaPonto(cx,cy);

    return pnt;

}


long double areaPoligono(poligono p){
    objPol *pol = (objPol*) p;
    ponto *array = pol->arrayPontos;
    long double area=0;

    for(int i=0;i < pol->tam; i++){

        if( i == pol->tam-1){
            area = (retornaPonto_X(array[i]) * retornaPonto_Y(array[0])) - (retornaPonto_X(array[0]) * retornaPonto_Y(array[i])) + area;
        }
        else{
            area = (retornaPonto_X(array[i]) * retornaPonto_Y(array[i+1])) - (retornaPonto_X(array[i+1]) * retornaPonto_Y(array[i])) + area;
        }
       
    }

    area = -1*area/2;

    return area;
}

char *retornaPoligono_Cor(poligono p){
    objPol *pol = (objPol*) p;
    return pol->cor;
}


int retornaPoligono_Tam(poligono p){
    objPol *pol = (objPol*) p;
    return pol->tam;
}

ponto *retornaArrayPontos(poligono p){
    objPol *pol = (objPol*) p;
    return pol->arrayPontos;
}

void removePoligono(poligono p){
    objPol *pol = (objPol*) p;

    for(int i=0;i < pol->tam;i++){
        free(pol->arrayPontos[i]);
    }

    free(pol->arrayPontos);
    free(pol);
}
