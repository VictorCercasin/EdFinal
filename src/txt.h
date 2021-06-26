#ifndef txt_h
#define txt_h

#include "lista.h"
#include "quadtree.h"
#include "morador.h"
#include "pessoa.h"
#include "estabComerc.h"

/*
*   cria o arquivo txt
*   necessita da path do arquivo txt
*   não retorna nada
*/
void criarTxt(char *path);

/*
*   preenche o arquivo txt
*   necessita da path do arquivo txt, dos tokens de leitura e a quantidade de tokens
*   não retorna nada
*/
void escreveTxt(char *path, char info[][50], int qtd);

/*
*   imprime Id, tipo e coordenadas de um objeto
*   necessita de um nódulo  e da path do arquivo txt
*   não retorna nada
*/
void imprimeElemento(char *path, nodulo elemento);

/*
*   completa com '\n' o arquivo txt
*   necessita da path do arquivo txt
*   não retorna nada
*/
void completarTxt(char *path);

/*
*   imprime resultado da sobreposição entre dois elementos no arquivo txt
*   necessita da path do arquivo txt e de 2 diferentes nódulos
*   não retorna nada
*/
void oTxt(char *path, nodulo node1, nodulo node2, char *resultado);

/*
*   imprime no arquivo TXT se o ponto está inserido ou não dentro de uma certa figura.
*   necessita da path do arquivo txt , do nódulo do elemento utilizado e o resultado da inserção
*   não retorna nada
*/
void iTxt(char *path, nodulo node, char *resultado);

/*
*   imprime no arquivo TXT as coordenadas de um ponto
*   necessita do arquivo TXT e de um objeto do tipo ponto
*   não retorna nada
*/
void pontoTxt(char *path, ponto p);

/*
*   imprime no arquivo TXT as informações de certos elementos
*   necessita do elemento utilizado e a path do arquivo txt
*   não retorna nada
*/
void pntTxt(char *path, Info info);

/*
*   imprime no arquivo TXT as informaçoes a respeito do comando ci
*   necessita da path do arquivo TXT, da area do poligono, do numero de casos e a incidencia
*   não retorna nada
*/
void comandoCiTxt(char *path, long double area, int numCasos, double incidencia);

/*
*   imprime no arquivo TXT as informaçoes a respeito do estabelecimento comercial recebido
*   necessita da path do arquivo TXT, do ponteiro para o objeto tipo estabComercial e da descricao do estabelecimento
*   não retorna nada
*/
void estabTxt(char *pathTXT, Modulo ec, char *desc);

/*
*   imprime os dados antigos do morador recebido, assim como os novos, recebidos por parametro
*   necessita da path do arquivo TXT, do ponteiro para o objeto tipo morador e dos novos dados da localizacao do morador
*   não retorna nada
*/
void mudancaTxt(char *pathTXT, Modulo mAntigo, char *cep, char face, int num, char *compl);

/*
*   imprime os dados principais do objeto tipo Morador recebido
*   necessita da path do arquivo TXT e do ponteiro para o objeto tipo morador
*   não retorna nada
*/
void moradorTxt(char *pathTXT, Modulo m);

/*
*   imprime em um arquivo as informações de um objeto
*   necessita de um nódulo
*   não retorna nada
*/
void delfTxt(char *path, Info info);

#endif