#ifndef leqry_h
#define leqry_h

#include <math.h>
#include "lista.h"
#include "info.h"
#include "svg.h"
#include "txt.h"
#include "casa.h"
#include "quadra.h"
#include "sort.h"
#include "poligono.h"
#include "quadtree.h"
#include "hashTable.h"
#include "str.h"
#include "grafo.h"
#include "estabComerc.h"

/*
*   a função é responsável por direcionar tudo relacionado ao arquivo qry à diferentes funções auxiliares
*   necessita da path do arquivo txt , as quadtrees, listas e hashtables, assim como a quantidade de tokens e os tokens, do grafo, arvore geradora minima e path auxiliar de svg
*   não retorna nada
*/
void menuQRY(char *pathTXT, Grafo grafo, Grafo *arvoreGeradoraMin, ponto *R, Lista moradores, Lista listQRY, QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree torresCel, QuadTree semaforos, QuadTree quadras ,QuadTree regioes, QuadTree casas, QuadTree postos, Lista poligonos, char info[][50],int qtd, HashTable cepXquadra, HashTable cpfXpessoa, HashTable codtXdesc, HashTable cpfXcep,  Lista estabComerc, char **pathSvgAuxiliar);

/*
*   verifica se o elemento recebido está ou não dentro de um círculo
*   necessita de um objeto contendo os dados do elemento e as informações do círculo
*   retorna o resultado da verificação (0, caso dentro)
*/
int verificaInteriorCirc(double x, double y, double r, Info info);

/*
*   verifica se o elemento recebido está ou não dentro de um retângulo
*   necessita de um objeto contendo os dados do elemento e as informações do retângulo
*   retorna o resultado da verificação (0, caso dentro)
*/
int verificaInteriorRet(double r_x1, double r_y1, double r_x2,  double r_y2, Info info);


#endif

