#ifndef __info_h
#define __info_h

#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "ponto.h"
#include "regiao.h"
#include "poligono.h"
#include "casa.h"
#include "str.h"

typedef void *Modulo;
typedef void *Info;
typedef void *Objeto;

/*
*   cria um objeto do tipo Info
*   necessita das informações de tipo e posição/id do elemento, assim como o elemento
*   retorna um ponteiro para o objeto tipo Info
*/
Info montaInfo(char *tipo, char *pos, Modulo elemento);

/*
*   necessita de um objeto tipo info
*   retorna a pos/Id do info recebido
*/
char *retornaPos(Info inf);

/*
*   necessita de um objeto tipo info
*   retorna o tipo do info recebido
*/
char *retornaTipo(Info inf);

/*
*   pega o ponteiro para o objeto do tipo ponto associado ao Info recebido
*   retorna ponteiro para o objeto do tipo ponto
*/
ponto retornaInfoCoord(Info info);

/*
*   deleta o objeto do tipo info recebido
*   necessita de um objeto do tipo info
*   não retorna nada
*/
void removeInfo(Info inf);

/*  
*   necessita de um objeto do tipo info
*   retorna o elemento dentro do objeto Info
*/
Modulo getModulo(Info inf);



#endif