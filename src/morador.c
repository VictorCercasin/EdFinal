#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "morador.h"

typedef struct m
{       
    Pessoa p;
    ponto pnt;
    char cep[100];
    char face;
    int num;
    char compl[100];
} morador;


Morador montaMorador(Pessoa p, Quadra quadra, char face, int num, char *compl){
    
        morador *m = malloc(sizeof(morador));
        m->p = p;
        m->pnt = montaPonto(-1,-1);

        alteraMorador_Endereco(m,quadra,face,num,compl);
        
        return m;
}

void alteraMorador_Endereco(Morador m, Quadra quadra, char face, int num, char *compl){
    
    morador *mor = (morador*)m;

    strcpy(mor->cep,retornaQuadra_Cep(quadra));
    strcpy(mor->compl,compl);
    mor->face = face;
    mor->num = num;

    double xQuadra = retornaQuadra_X(quadra), yQuadra = retornaQuadra_Y(quadra), wQuadra = retornaQuadra_W(quadra), hQuadra = retornaQuadra_H(quadra);
    
    switch(face){
        case 'S':
            alteraPonto_X(mor->pnt,xQuadra + num);
            alteraPonto_Y(mor->pnt,yQuadra);
            break;
        case 'N':
            alteraPonto_X(mor->pnt,xQuadra + num);
            alteraPonto_Y(mor->pnt,yQuadra + hQuadra);
            break;
        case 'L':
            alteraPonto_X(mor->pnt,xQuadra);
            alteraPonto_Y(mor->pnt,yQuadra + num);
            break;
        case 'O':
            alteraPonto_X(mor->pnt,xQuadra + wQuadra);
            alteraPonto_Y(mor->pnt,yQuadra + num);
            break;
    }
}

char *retornaMorador_Cep(Morador m){
    morador *mor = (morador*)m;
    return mor->cep;
}

char retornaMorador_Face(Morador m){
    morador *mor = (morador*)m;
    return mor->face;
}

int retornaMorador_Num(Morador m){
    morador *mor = (morador*)m;
    return mor->num;
}

char *retornaMorador_Compl(Morador m){
    morador *mor = (morador*)m;
    return mor->compl;
}

Pessoa retornaMorador_Pessoa(Morador m){
    morador *mor = (morador*)m;
    return mor->p;
}

ponto retornaMorador_Ponto(Morador m){
    morador *mor = (morador*)m;
    return mor->pnt;
}

void removeMorador(Morador m){
    morador *mor = (morador*)m;
    removePonto(mor->pnt);
    free(mor);
}