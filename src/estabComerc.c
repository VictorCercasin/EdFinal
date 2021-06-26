#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estabComerc.h"

typedef struct estabComerc
{
    Pessoa p;
    ponto pnt;
    char cep[100];
    char cnpj[100];
    char face;
    int num;
    char codt[100];
    char nome[100];
} ec;

estabComercial montaEstab(Pessoa p, Quadra quadra, char face, int num, char *cnpj, char *codt, char *nome){
    
        ec *estab = malloc(sizeof(ec));
        estab->p = p;
        strcpy(estab->nome, nome);
        strcpy(estab->cnpj, cnpj);
        strcpy(estab->codt, codt);
        estab->pnt = montaPonto(-1,-1);
        alteraEstab_Endereco(estab,quadra,face,num);
        
        return estab;
}

void alteraEstab_Endereco(estabComercial est, Quadra quadra, char face, int num){
    
    ec *estab = (ec*) est;

    strcpy(estab->cep,retornaQuadra_Cep(quadra));
    estab->face = face;
    estab->num = num;

    double xQuadra = retornaQuadra_X(quadra), yQuadra = retornaQuadra_Y(quadra), wQuadra = retornaQuadra_W(quadra), hQuadra = retornaQuadra_H(quadra);
    
    switch(face){
        case 'S':
            alteraPonto_X(estab->pnt,xQuadra + num);
            alteraPonto_Y(estab->pnt,yQuadra);
            break;
        case 'N':
            alteraPonto_X(estab->pnt,xQuadra + num);
            alteraPonto_Y(estab->pnt,yQuadra + hQuadra);
            break;
        case 'L':
            alteraPonto_X(estab->pnt,xQuadra);
            alteraPonto_Y(estab->pnt,yQuadra + num);
            break;
        case 'O':
            alteraPonto_X(estab->pnt,xQuadra + wQuadra);
            alteraPonto_Y(estab->pnt,yQuadra + num);
            break;
    }
}

void removeEc(estabComercial est){
    ec* estab = (ec*) est;

    free(estab->pnt);
    free(estab);
}

Pessoa getEstab_Pessoa(estabComercial est){
    ec* estab = (ec*) est;

    return estab->p;
}

ponto getEstab_Ponto(estabComercial est){
    ec* estab = (ec*) est;

    return estab->pnt;
}

char *getEstab_Cnpj(estabComercial est){
    ec* estab = (ec*) est;

    return estab->cnpj;
}

char *getEstab_Cep(estabComercial est){
    ec* estab = (ec*) est;

    return estab->cep;
}

char *getEstab_Nome(estabComercial est){
    ec* estab = (ec*) est;

    return estab->nome;
}

char getEstab_Face(estabComercial est){
    ec* estab = (ec*) est;

    return estab->face;
}

int getEstab_Num(estabComercial est){
    ec* estab = (ec*) est;

    return estab->num;
}

char *getEstab_Codt(estabComercial est){
    ec* estab = (ec*) est;

    return estab->codt;
}

