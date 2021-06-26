#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "quadra.h"

typedef struct q{
    char corp[100], corb[100];
    char cep[100], sw[100];
    char corSombra[100];
    double w, h;
    ponto coord;

    int casosCovidFace_N;
    int casosCovidFace_S;
    int casosCovidFace_L;
    int casosCovidFace_O;

}objQuad;

Quadra montaQuadra(char *id,char *sw ,double w,double h, double x, double y, char *corb, char *corp){

        objQuad *q;
        q = (objQuad *) calloc (1, sizeof(objQuad));

        if(corp!=NULL && corb != NULL){
                if(corp[strlen(corp)-1]=='\n'){
                        corp[strlen(corp)-1]='\0'; // Para tirar o '\n'
                }
                strcpy(q->corp, corp);
                strcpy(q->corb, corb);
                strcpy(q->corSombra, "white");
        }

        strcpy(q->cep,id);
        strcpy(q->sw, sw);

        ponto pt = montaPonto(x,y);

        q->casosCovidFace_N = 0;
        q->casosCovidFace_L = 0;
        q->casosCovidFace_O = 0;
        q->casosCovidFace_S = 0;

        q->coord = pt;

        q->w = w;
        q->h = h;
        
        return q;
}

void addCasosCovid(Quadra q, char *face, int numCasos){

        objQuad *quad = (objQuad *) q;

        if(strcmp(face,"L")==0){
               quad->casosCovidFace_L += numCasos;
        }
        
        else if(strcmp(face,"O")==0){
               quad->casosCovidFace_O += numCasos;
        }
        
        else if(strcmp(face,"S")==0){
               quad->casosCovidFace_S += numCasos;
        }

        else if(strcmp(face,"N")==0){
               quad->casosCovidFace_N += numCasos;
        }
}

int numCasosFace(Quadra q, char *face){

        objQuad *quad = (objQuad *) q;

        if(strcmp(face,"L")==0){
               return quad->casosCovidFace_L;
        }
        
        else if(strcmp(face,"O")==0){
               return quad->casosCovidFace_O;
        }
        
        else if(strcmp(face,"S")==0){
               return quad->casosCovidFace_S;
        }

        else if(strcmp(face,"N")==0){
               return quad->casosCovidFace_N;
        }
}

double retornaQuadra_X(Quadra q){
        objQuad *quad = (objQuad *) q;
        return retornaPonto_X(quad->coord);
}

double retornaQuadra_Y(Quadra q){
        objQuad *quad = (objQuad *) q;
        return retornaPonto_Y(quad->coord);
}

double retornaQuadra_W(Quadra q){
        objQuad *quad = (objQuad *) q;
        return quad->w;
}

double retornaQuadra_H(Quadra q){
        objQuad *quad = (objQuad *) q;
        return quad->h;
}

char *retornaQuadra_Cep(Quadra q){
        objQuad *quad = (objQuad *) q;
        return quad->cep;
}

char *retornaQuadra_SW(Quadra q){
        objQuad *quad = (objQuad *) q;
        return quad->sw;
}

char *retornaQuadra_Corp(Quadra q){
        objQuad *quad = (objQuad *) q;
        return quad->corp;
}

char *retornaQuadra_Corb(Quadra q){
        objQuad *quad = (objQuad *) q;
        return quad->corb;
}

char *retornaQuadra_CorSombra(Quadra q){
        objQuad *quad = (objQuad *) q;
        return quad->corSombra;
}

void removeQuadra(Quadra q){
        objQuad *quad = (objQuad *) q;
        free(quad->coord);
        free(quad);
}

ponto retornaQuadraCoord(Quadra q){
        objQuad *quad = (objQuad *) q;
        return quad->coord;
}

void alteraQuadra_Corb(Quadra q, char *corb){
        objQuad *quad = (objQuad *) q;
        strcpy(quad->corb,corb);

        return;
}

void alteraQuadra_CorSombra(Quadra q, char *cors){
        objQuad *quad = (objQuad *) q;
        strcpy(quad->corSombra,cors);

        return;
}

void alteraQuadra_Corp(Quadra q, char *corp){
        objQuad *quad = (objQuad *) q;
        strcpy(quad->corp,corp);

        return;
}

