#ifndef hashtable_h
#define hashtable_h

#include "lista.h"
#include "info.h"

typedef void *HashTable;

/*
*   cria uma hashtable vazia
*   necessita do numero de entradas
*   retorna ponteiro para a hashtable
*/
HashTable criaHt(int numEntradas);

int numEntradasHt(HashTable ht);

void removeItens(HashTable ht);

Lista listaItensHt_lista(HashTable ht, int indice);

/*
*   procura um elemento na hashtable 
*   necessita de uma string chave (str)
*   retorna ponteiro para elemento encontrado ou null caso nao seja encontrado
*/
void *searchHash(HashTable hashTable, char *str);

/*
*   insere um elemento na hashtable
*   necessita do ponteiro para hashtable, de uma string chave e do ponteiro para o valor (item)
*   nao retorna nada
*/
void insereHT(HashTable hashTable, char *chave, void *item);

/*
*   remove um elemento da hashtable
*   necessita de um ponteiro para a hashtable e de uma string chave
*   retorna ponteiro para o conteudo (Info) do objeto deletado
*/
void *removeHT(HashTable hashTable, char *chave);

/*
*   desaloca a hashtable sem deletar o conteudo (Info) de cada elemento
*   necessita de um ponteiro para a hashtable
*   nao retorna nada
*/
void desalocaHT(HashTable hashTable);

/*
*   desaloca a hashtable, deletando o conteudo (Info) de cada elemento
*   necessita de um ponteiro para a hashtable
*   nao retorna nada
*/
void desalocaHT_del(HashTable hashTable);

#endif