#ifndef learq_h
#define learq_h

#include "lista.h"
#include "quadtree.h"
#include "hashTable.h"
#include "pessoa.h"
#include "morador.h"
#include "estabComerc.h"
#include "grafo.h"

/*
*   Separa cada palavra de uma linha em diferentes tokens
*   necessita de uma linha(string) e de um vetor de strings
*   retorna a quantidade de tokens separados
*/
int funcLer(char *line, char mat[][50]);

/*
*   Lê o arquivo de path recebida, cria os objetos requeridos e os envia para diferentes listas
*   necessita das listas, quadtrees e a path do arquivo
*   não retorna nada
*/
void lerArqGeo(char *arq, HashTable cepXquadra, QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree quadras, QuadTree torresCelular, QuadTree semaforos, QuadTree postos, QuadTree regioes);

/*
*   Lê o arquivo de path recebida, cria os objetos requeridos e os envia para diferentes listas
*   necessita da lista de moradores, hashtables e a path do arquivo
*   não retorna nada
*/
void lerArqPm(char *arq,Lista moradores, HashTable cpfXpessoa, HashTable cepXquadra, HashTable cpfXcep);

/*
*   Lê o arquivo de path recebida, cria os objetos requeridos e os envia para diferentes listas
*   necessita da lista de estabelecimentos comerciais, das hashtables e a path do arquivo
*   não retorna nada
*/
void lerArqEc(char *arq, HashTable codtXdesc, HashTable cpfXpessoa, Lista estabComerc, HashTable cepXquadra);

/*
*   Lê o arquivo de path recebida
*   necessita do arquivo via
*   retorna o grafo criado
*/
Grafo lerArqVia(char *arq);

#endif 