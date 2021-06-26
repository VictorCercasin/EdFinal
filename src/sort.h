#ifndef __sort_h
#define __sort_h

#include "ponto.h"
#include "info.h"


double distSq(ponto p1, ponto p2);

/*
*   calcula a envoltoria convexa dado um vetor de pontos
*   necessita de um vetor de pontos e da quantidade de pontos
*   retorna o poligono com seus pontos ordenados
*/
Lista envoltoriaConvexa(Info *array, int n);

/*
*   ordena os elementos de um vetor
*   necessita de um vetor, da primeira posicao e ultima
*   não retorna nada
*/
void quickSort(void *array, int low, int high);

/*
*   ordena os elementos de um vetor de pontos
*   necessita de um vetor, de seu tamanho e de um ponto de referencia
*   retorna o vetor de pontos ordenado
*/
ponto *shellSort(ponto *vet, int size, int k, ponto ref, int *tamanhoResultado);

#endif