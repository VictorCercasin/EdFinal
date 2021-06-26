#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pessoa.h"

typedef struct p
{
    char cpf[100];
    char nome[100];
    char sobrenome[100];
    char sexo;
    char nasc[100];
} pessoa;


Pessoa montaPessoa(char *cpf,char *nome, char *sobrenome, char sexo, char *nasc){
        pessoa *p = malloc(sizeof(pessoa));

        strcpy(p->cpf,cpf);
        strcpy(p->nome,nome);
        strcpy(p->sobrenome,sobrenome);
        p->sexo = sexo;
        strcpy(p->nasc,nasc);
        
        return p;
}

char *retornaPessoa_Cpf(Pessoa p){
    pessoa *pes = (pessoa*)p;
    return pes->cpf;
}

char *retornaPessoa_Nome(Pessoa p){
    pessoa *pes = (pessoa*)p;
    return pes->nome;
}

char *retornaPessoa_Sobrenome(Pessoa p){
    pessoa *pes = (pessoa*)p;
    return pes->sobrenome;
}

char retornaPessoa_Sexo(Pessoa p){
    pessoa *pes = (pessoa*)p;
    return pes->sexo;
}

char *retornaPessoa_Nasc(Pessoa p){
    pessoa *pes = (pessoa*)p;
    return pes->nasc;
}

void removePessoa(Pessoa p){
    pessoa *pes = (pessoa*)p;
    free(pes);
}


