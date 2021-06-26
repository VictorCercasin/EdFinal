#ifndef morador_h
#define morador_h


#include "retangulo.h"
#include "pessoa.h"
#include "quadra.h"

typedef void *Morador;

/*
*   cria um objeto do tipo Morador
*   necessita das informacoes do morador, um ponteiro para o objeto Quadra (onde reside) e um ponteiro para um objeto do tipo Pessoa
*   retorna um ponteiro para o objeto de tipo Morador
*/
Morador montaMorador(Pessoa p, Quadra quadra, char face, int num, char *compl);

/*
*   altera o endereco de um morador
*   necessita das informacoes do endereco novo, um ponteiro para Quadra e ponteiro para Morador
*   não retorna nada
*/
void alteraMorador_Endereco(Morador m, Quadra quadra, char face, int num, char *compl);

/*
*   pega o Cep do morador
*   necessita de ponteiro para o objeto tipo Morador
*   retorna o cep do morador (string)
*/
char *retornaMorador_Cep(Morador m);

/*
*   pega a face do morador
*   necessita de ponteiro para o objeto tipo Morador
*   retorna a face do morador (char)
*/
char retornaMorador_Face(Morador m);

/*
*   pega o numero do morador
*   necessita de ponteiro para o objeto tipo Morador
*   retorna o numero do morador (inteiro)
*/
int retornaMorador_Num(Morador m);

/*
*   pega o complemento do morador
*   necessita de ponteiro para o objeto tipo Morador
*   retorna o complemento do morador (string)
*/
char *retornaMorador_Compl(Morador m);

/*
*   pega a pessoa contida no objeto tipo Morador
*   necessita de ponteiro para o objeto tipo Morador
*   retorna o ponteiro para objeto tipo Pessoa
*/
Pessoa retornaMorador_Pessoa(Morador m);

/*
*   pega o ponto (coordenadas) do morador
*   necessita de ponteiro para o objeto tipo Morador
*   retorna o ponteiro para objeto tipo ponto
*/
ponto retornaMorador_Ponto(Morador m);

/*
*   deleta o objeto tipo Morador
*   necessita de ponteiro para o objeto tipo Morador
*   nao retorna nada
*/
void removeMorador(Morador m);

#endif