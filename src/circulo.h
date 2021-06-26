#ifndef __circulo_h
#define __circulo_h

#include "ponto.h"

typedef void *circulo; 

/*
*   cria um objeto do tipo círculo
*   necessita das informações do circulo
*   retorna um objeto tipo círculo
*/
circulo montaCirculo(char *id, char *sw, double raio, double x, double y, char *corb, char *corp);

/*
*   necessita de um objeto do tipo círculo
*   retorna x do circulo recebido
*/
double retornaCirc_X(circulo c);

/*
*   necessita de um objeto do tipo círculo
*   retorna y do circulo recebido
*/
double retornaCirc_Y(circulo c);

/*
*   necessita de um objeto do tipo círculo
*   retorna r do circulo recebido
*/
double retornaCirc_Raio(circulo c);

/*
*   necessita de um objeto do tipo círculo
*   retorna id do circulo recebido
*/
char *retornaCirc_Id(circulo c);

/*
*   necessita de um objeto do tipo círculo
*   retorna a largura da borda do circulo recebido
*/
char *retornaCirc_SW(circulo c);

/*
*   necessita de um objeto do tipo círculo
*   retorna cor de preenchimento do circulo recebido
*/
char *retornaCirc_Corp(circulo c);

/*
*   necessita de um objeto do tipo círculo
*   retorna cor da borda do circulo recebido
*/
char *retornaCirc_Corb(circulo c);


/*  altera a cor de borda do circulo recebido
*   necessita de um objeto do tipo círculo e de uma string corp (cor de preenchimento)
*   não retorna nada
*/
void alteraCirc_Corb(circulo c, char *corb);

/*  altera a cor de preenchimento do circulo recebido
*   necessita de um objeto do tipo círculo e de uma string corb(cor de borda)
*   não retorna nada
*/
void alteraCirc_Corp(circulo c, char *corp);

/*
*   pega as coordenadas do circulo
*   necessita de um objeto do tipo circulo
*   retorna o objeto ponto contendo as coordenadas x,y do circulo recebido
*/
ponto retornaCircCoord(circulo c);

/*  deleta o objeto de tipo circulo
*   necessita de um objeto do tipo círculo 
*   não retorna nada
*/
void removeCirculo(circulo c);

#endif