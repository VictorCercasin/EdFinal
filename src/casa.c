#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "casa.h"
#include "quadtree.h"
#include "ponto.h"

typedef struct casa
{ 
    int n;
    char face;
    double w, h, n_x, n_y;
    ponto coord;
} objCasa;

casa montaCasa(int n, char *cep, char *face, int num, QuadTree quadras){

        double quad_x, quad_y, quad_w, quad_h;

        objCasa *c;
        c = (objCasa *) calloc (1, sizeof(objCasa));
        
        c->n = n;
        c->face = face[0];

        nodulo node =  getNoQt_byId(quadras, cep);

        if(node == NULL){
                return NULL;
        }

        c->w = 10;
        c->h = 10;

        Modulo quad = getModulo(getInfoQt(quadras,node));
        addCasosCovid(quad, face, n);

        quad_x = retornaQuadra_X(quad);
        quad_y = retornaQuadra_Y(quad);
        quad_w = retornaQuadra_W(quad);
        quad_h = retornaQuadra_H(quad);

        if(strcmp(face,"L")==0){
                c->n_y = quad_y + num + 3.5;
                c->n_x = quad_x + c->w/2 + 1;

                ponto pt = montaPonto(quad_x+1, quad_y+num-c->h/2+1);
                c->coord = pt;
        }
        
        else if(strcmp(face,"O")==0){
                c->n_y = quad_y + num + c->h/2 - 3;
                c->n_x = quad_x + quad_w - c->w/2 - 1;

                ponto pt = montaPonto(quad_x + quad_w - c->w - 1, quad_y + num - c->h/2);
                c->coord = pt;
        }
        
        else if(strcmp(face,"S")==0){
                c->n_y = quad_y + c->h/2 + 3.5;
                c->n_x = quad_x + num;

                ponto pt = montaPonto(quad_x + num - c->w/2, quad_y + 1);
                c->coord = pt;
        }

        else if(strcmp(face,"N")==0){
                c->n_y = quad_y + quad_h - c->h/2 + 1.5;
                c->n_x = quad_x + num;

                ponto pt = montaPonto(c->n_x - c->w/2, quad_y + quad_h - c->h - 1);
                c->coord = pt;
        }

        return c;
}

ponto pontoCentral_Endereco(Quadra quad,char *face, int num){

        double quad_x = retornaQuadra_X(quad);
        double quad_y = retornaQuadra_Y(quad);
        double quad_w = retornaQuadra_W(quad);
        double quad_h = retornaQuadra_H(quad);
        
        double n_y,n_x,x,y,w=10,h=10;

        if(strcmp(face,"L")==0){
                x = quad_x + 1;
                y = quad_y + num - h/2 + 1;
        }
        
        else if(strcmp(face,"O")==0){
                x = quad_x + quad_w - w - 1;
                y = quad_y + num - h/2;
        }
        
        else if(strcmp(face,"S")==0){
                x = quad_x + num - w/2;
                y = quad_y + 1;
        }

        else if(strcmp(face,"N")==0){
                x = quad_x + num - w/2;
                y = quad_y + quad_h - h - 1;
        }

        ponto pc = montaPonto(x+w/2,y+h/2);

        return pc;
}

double retornaCasa_Xc(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return retornaPonto_X(casa_atual->coord) + casa_atual->w/2;
}

double retornaCasa_Yc(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return retornaPonto_Y(casa_atual->coord) + casa_atual->h/2;
}

int retornaCasa_N(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return casa_atual->n;
}

double retornaCasa_X(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return retornaPonto_X(casa_atual->coord);
}

double retornaCasa_Y(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return retornaPonto_Y(casa_atual->coord);
}

double retornaCasa_W(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return casa_atual->w;
}

double retornaCasa_H(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return casa_atual->h;
}

double retornaCasa_Ny(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return casa_atual->n_y;
}

double retornaCasa_Nx(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return casa_atual->n_x;
}

void removeCasa(casa c){
        objCasa *casa_atual = (objCasa *) c;
        free(casa_atual->coord);
        free(casa_atual);
}

ponto retornaCasaCoord(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return casa_atual->coord;
}

char retornaCasaFace(casa c){
        objCasa *casa_atual = (objCasa *) c;
        return casa_atual->face;
}