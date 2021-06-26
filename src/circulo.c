#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "circulo.h"
#include "ponto.h"

typedef struct circle
{
    char corp[100], corb[100];
    char id[100], sw[100];
    double r; //x e y
    ponto coord;
} objCirc;

circulo montaCirculo(char *id,char *sw, double raio, double x, double y, char *corb, char *corp){

        objCirc *circ;
        circ = (objCirc *) malloc (sizeof(objCirc));

        strcpy(circ->id, id);

        if(corp[strlen(corp)-1]=='\n'){
                corp[strlen(corp)-1]='\0';
        } // Para não haver '\n', trocamos ele por '\0'
        strcpy(circ->corp, corp);
        strcpy(circ->corb, corb);

        strcpy(circ->sw, sw);

        ponto pt = montaPonto(x,y);

        circ->coord = pt;
        circ->r = raio;
        
        return circ;
}


double retornaCirc_X(circulo c){
        objCirc *circ = (objCirc *) c;
        return retornaPonto_X(circ->coord);
}

double retornaCirc_Y(circulo c){
        objCirc *circ = (objCirc *) c;
        return retornaPonto_Y(circ->coord);
}

double retornaCirc_Raio(circulo c){
        objCirc *circ = (objCirc *) c;
        return circ->r;
}

char *retornaCirc_Id(circulo c){
        objCirc *circ = (objCirc *) c;
        return circ->id;
}

char *retornaCirc_SW(circulo c){
        objCirc *circ = (objCirc *) c;
        return circ->sw;
}

char *retornaCirc_Corp(circulo c){
        objCirc *circ = (objCirc *) c;
        return circ->corp;
}

char *retornaCirc_Corb(circulo c){
        objCirc *circ = (objCirc *) c;
        return circ->corb;
}

void alteraCirc_Corb(circulo c, char *corb){
        objCirc *circ = (objCirc *) c;
        strcpy(circ->corb,corb);

        return;
}

void alteraCirc_Corp(circulo c, char *corp){
        objCirc *circ = (objCirc *) c;
        strcpy(circ->corp,corp);

        return;
}

void removeCirculo(circulo c){
        objCirc *circ = (objCirc *) c;
        free(circ->coord);
        free(circ);
}

ponto retornaCircCoord(circulo c){
        objCirc *circ = (objCirc *) c;
        return circ->coord;
}