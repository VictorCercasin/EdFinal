#ifndef lista_h
#define lista_h

#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "info.h" 
#include "ponto.h"
#include "regiao.h"
#include "poligono.h"
#include "casa.h"
#include "estabComerc.h"
#include "morador.h"

typedef void *Lista;
typedef void *nodulo;
typedef void *Info;

/*
*   transforma um inteiro em string
*   necessita de um inteiro
*   retorna uma string
*/
char *transfIntString(int dado);

/*
*   cria uma lista 
*   não necessita de nada
*   retorna uma lista vazia
*/
Lista criarLista();

/*
*   cria um vetor de listas
*   necessita do tamanho do vetor desejado
*   retorna um ponteiro para o vetor de listas
*/
void *criarVetorLista(int n);

/*
*   remove o primeiro elemento da lista
*   necessita da lista
*   retorna um ponteiro para o objeto do tipo Info
*/
Info removeFirst(Lista listagem);

/*
*   remove o ultimo elemento da lista
*   necessita da lista
*   retorna um ponteiro para o objeto do tipo Info
*/
Info removeLast(Lista listagem);

/*
*   deleta um modulo e info de um elemento da lista e o deleta
*   necessita de um nódulo e a lista onde está presente
*   não retorna nada
*/
void removerElemento(Lista listagem, nodulo elemento);

/*
*   pega o próximo elemento
*   necessita de um nódulo
*   retorna o nódulo subsequente ao recebido
*/
nodulo getNext(nodulo elemento);

/*
*   pega o último elemento de uma lista
*   necessita de uma lista 
*   retorna o último nódulo da lista recebida
*/
nodulo getLast(Lista lista);

/*
*   pega o primeiro elemento de uma lista
*   necessita de uma lista
*   retorna o primeito elemento da lista recebida
*/
nodulo getFirst(Lista lista);

/*
*   pega o nódulo anterior
*   necessita de um nódulo
*   retorna o nódulo anterior ao recebido
*/
nodulo getPrevious(nodulo elemento);

/*
*   pega o ponteiro para objeto do tipo Info
*   necessita de um nódulo
*   retorna o ponteiro para o objeto tipo info do nódulo recebido
*/
Info getInfo(nodulo elemento);

/*
*   cria um nodulo, contendo um certo info e insere em uma determinada lista
*   necessita de uma lista, um objeto tipo Modulo e um objeto tipo Info
*   não retorna nada
*/
void insertAfterLast(Lista listagem, Info info);

/*
*   cria um nodulo, contendo um certo info e insere em uma determinada lista apos um certo nodulo
*   necessita de uma lista, um objeto tipo Info e de um nodulo
*   não retorna nada
*/
void insertAfter(nodulo nodeAnt, Info info, Lista listagem);

/*
*   cria um nodulo, contendo um certo info e insere em uma determinada lista antes de um certo nodulo
*   necessita de uma lista, um objeto tipo Info e de um nodulo
*   não retorna nada
*/
void insertBefore(nodulo nodeProx, Info info, Lista listagem);

/*
*   libera a memoria armazenada por todas as listas
*   necessita de todas as listas
*   não retorna nada
*/
void limparMemoria(Lista figuras, Lista hidrantes, Lista semaforos, Lista quadras, Lista torresCel, Lista listQRY, Lista postos, Lista regioes, Lista casas, Lista poligonos);

/*
*   libera a memoria armazenada por uma lista
*   necessita de uma lista
*   não retorna nada
*/
void limparLista(Lista listagem);

/*
*   procura um node a partir de diversas listas
*   necessita de todas as listas e da id/cep de um elemento
*   retorna o nódulo procurado
*/
nodulo searchNode(Lista hidrantes, Lista semaforos, Lista quadras, Lista torresCel, char *id);

/*
*   procura um nodulo que possui o objeto do tipo Info recebido
*   necessita de uma lista e de um objeto do tipo Info 
*   retorna o nodulo, caso seja encontrado, ou nulo, caso nao encontre
*/
nodulo findNode_byInfo(Lista listagem, Info info);

/*
*   procura um node em uma lista específica
*   necessita de uma lista e de um id/cep de um elemento
*   retorna o nódulo procurado (caso encontrado) ou nulo
*/
nodulo findNode(Lista listagem, char *id);

/*
*   deleta o nódulo 
*   necessita de um nódulo e de sua lista
*   retorna o ponteiro para o objeto tipo Info (contido no nodulo) que deve ser desalocado separadamente
*/
Info removeNode(nodulo node, Lista listagem);

/*
*   procura a lista de um elemento específico dentre todas
*   necessita de todas as listas e um id/cep de um elemento
*   retorna a lista procurada
*/
Lista searchLista(Lista figuras, Lista hidrantes, Lista semaforos, Lista quadras, Lista torresCel, char *id);

/*
*   transforma uma String em um inteiro
*   necessita de uma string
*   retorna um inteiro
*/
int transfStringInt(char *dado);

/*
*   pega o tamanho de uma lista
*   necessita de uma lista
*   retorna o tamanho da lista
*/
int listSize(Lista listagem);

/*
*   transforma uma String em um double
*   necessita de uma string
*   retorna um objeto double
*/
double transfStringDouble(char *dado);

/*
*   libera a memoria armazenada por uma lista, menos o conteudo (Info) contido em cada nodulo
*   necessita de uma lista
*   não retorna nada
*/
void limparLista_aux(Lista listagem);


#endif