#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "texto.h"

typedef struct text
{
    char corp[100], corb[100];
    char *conteudo;
    char id[100];
    ponto coord;
} objTexto;

texto montaTexto(char *id, double x, double y, char *corb, char *corp, char *conteudo, int TotalLen){
          
    objTexto *texto = (objTexto *) malloc(sizeof(objTexto));
    texto-> conteudo = (char *)malloc(TotalLen);
    strcpy(texto->corp, corp);

    strcpy(texto->corb, corb);
    strcpy(texto->conteudo,conteudo);
    strcpy(texto->id, id);
  
    ponto pt = montaPonto(x,y);

    texto->coord = pt;
        
    return texto;
}

void alteraTexto_Corp(texto t, char *corp){
        objTexto *text = (objTexto *) t;
        strcpy(text->corp,corp);

        return;
}

void alteraTexto_Corb(texto t, char *corb){
        objTexto *text = (objTexto *) t;
        strcpy(text->corb,corb);

        return;
}

double retornaTexto_X(texto t){
    objTexto *texto = (objTexto *) t;
    return retornaPonto_X(texto->coord);
}

double retornaTexto_Y(texto t){
    objTexto *texto = (objTexto *) t;
    return retornaPonto_Y(texto->coord);
}

char *retornaTexto_Id(texto t){
    objTexto *texto = (objTexto *) t;
    return texto->id;    
}

char *retornaTexto_Corp(texto t){
    objTexto *texto = (objTexto *) t;
    return texto->corp;    
}

char *retornaTexto_Corb(texto t){
    objTexto *texto = (objTexto *) t;
    return texto->corb;    
}

char *retornaConteudo(texto t){
    objTexto *texto = (objTexto *) t;
    return texto->conteudo;    
}

ponto retornaTextoCoord(texto t){
    objTexto *texto = (objTexto *) t;
    return texto->coord;
}

void removeTexto(texto t){
    objTexto *texto = (objTexto *) t;

    free(texto->coord);
    free(texto->conteudo);
    free(texto);
}