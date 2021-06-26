#ifndef __casa_h
#define __casa_h

#include "lista.h"
#include "quadra.h"

typedef void *casa;
typedef void *lista_atual;
typedef void *nodulo_atual;

/*
*   cria um objeto do tipo casa
*   necessita das informações da casa
*   retorna um objeto do tipo casa
*/
casa montaCasa(int n, char *cep, char *face, int num, lista_atual quadras);

/*
*   cria um objeto do tipo ponto que representa o ponto central do quadrado do comando 'soc'
*   necessita de uma quadra, da face e num especificos da casa
*   retorna um objeto do tipo ponto
*/
ponto pontoCentral_Endereco(Quadra quad,char *face, int num);

/*
*   pega o numero de infectados do covid da casa 
*   necessita de um objeto do tipo casa
*   retorna o n da casa recebida
*/
int retornaCasa_N(casa c);

/*
*   pega a coordenada x do centro da casa
*   necessita de um objeto do tipo casa
*   retorna o x do centro da casa recebida
*/
double retornaCasa_Xc(casa c);

/*
*   pega a coordenada y do centro da casa
*   necessita de um objeto do tipo casa
*   retorna o y do centro da casa recebida
*/
double retornaCasa_Yc(casa c);

/*
*   pega a coordenada do x da casa
*   necessita de um objeto do tipo casa
*   retorna o x da casa recebida
*/
double retornaCasa_X(casa c);

/*
*   pega a coordenada y da casa
*   necessita de um objeto do tipo casa
*   retorna o y da casa recebida
*/
double retornaCasa_Y(casa c);

/*
*   pega a largura da casa
*   necessita de um objeto do tipo casa
*   retorna a largura da casa recebida
*/
double retornaCasa_W(casa c);

/*
*   pega a altura da casa
*   necessita de um objeto do tipo casa
*   retorna a altura da casa recebida
*/
double retornaCasa_H(casa c);

/*
*   pega a coordenada y do texto no centro da casa
*   necessita de um objeto do tipo casa
*   retorna o y do texto da casa recebida
*/
double retornaCasa_Ny(casa c);

/*
*   pega a coordenada x do texto no centro da casa
*   necessita de um objeto do tipo casa
*   retorna o x do texto da casa recebida
*/
double retornaCasa_Nx(casa c);

/*
*   pega as coordenadas da casa
*   necessita de um objeto do tipo casa
*   retorna o objeto ponto contendo as coordenadas x,y da casa recebida
*/
ponto retornaCasaCoord(casa c);

/*
*   deleta o objeto de tipo casa
*   necessita de um objeto do tipo casa
*   não retorna nada
*/
void removeCasa(casa c);

/*
*   pega a face do objeto tipo casa recebido
*   necessita de um objeto do tipo casa
*   retorna a face da casa (char)
*/
char retornaCasaFace(casa c);

#endif