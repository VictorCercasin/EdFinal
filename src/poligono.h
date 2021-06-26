#ifndef __poligono_h
#define __poligono_h

#include "ponto.h"

typedef void *poligono; 

/*
*   adiciona uma cor de preenchimento ao poligono
*   necessita de um poligono e de uma string de cor
*   não retorna nada
*/
void addCor(poligono p, char *cor);

/*
*   calcula a area do poligono
*   necessita de um poligono
*   retorna a area do poligono 
*/
long double areaPoligono(poligono p);

/*
*   pega a quantidade de pontos do poligono
*   necessita de um poligono
*   retorna a quantidade de pontos do poligono
*/
int retornaPoligono_Tam(poligono p);

/*
*   encontra o centroide de um poligono
*   necessita de um poligono e de sua area
*   retorna o centroide do poligono
*/
ponto encontrarCentroide(poligono poly, long double area);

/*
*   pega a cor de um poligono
*   necessita de um poligono
*   retorna a cor do poligono 
*/
char *retornaPoligono_Cor(poligono p);

/*
*   cria um poligono 
*   necessita de um vetor de pontos e da quantidade de pontos do vetor
*   retorna o ponteiro para o objeto do tipo poligono
*/
poligono montaPoligono(ponto *array, int tam);

/*
*   pega o vetor de pontos do poligono
*   necessita de um poligono
*   retorna o ponteiro para o vetor de pontos do poligono
*/
ponto *retornaArrayPontos(poligono p);

/*
*   deleta o poligono
*   necessita de um poligono
*   não retorna nada
*/
void removePoligono(poligono p);

#endif