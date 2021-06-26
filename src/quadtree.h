#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "ponto.h"
#include "string.h"


/*
     Implementa uma Point Quadtree. Uma quadtree vazia e criada pela operacao criaQt().
     Apos a criacao, dados associados a coordenadas bidimensionais podem ser inseridos
     por meio da operacao insereQt()

     Sao implementadas varias funcoes de busca espacial que retornam uma lista contendo
     as chaves, pontos ou nodulos da arvore que estejam dentro de um dado circulo ou retangulo.

     A arvore pode ser percorrida em largura ou em profundidade (percorreLarguraQt() e percorreProfundidadeQt()).
     Para cada nodulo visitado e invocada um procedimento que processa a informacao contida no nodulo visitado.
 */

typedef void *QuadTree;
typedef void *QtInfo;   
typedef void *QtNo;
typedef char *InfoKey;
typedef void *ExtraInfo;

typedef InfoKey funcGetChave(QtInfo);
typedef void visitaNo(QtInfo,ExtraInfo);

typedef void funcVisita(Info, ExtraInfo);


/**
    Cria e retorna uma quadtree vazia. "f" e uma funcao
    que retorna a chave de ordenacao do dado armazenado.
*/
QuadTree criaQt(funcGetChave f);

/**
    Cria uma lista contendo as chaves de ordenacaoo de todas as informacoes cujas coordenas associadas (no momento da insercao) estao dentro do
    retangulo determinado pelo vertices opostos (x1,y1) e (x2,y2).

    Memoria e alocada para cada chave armazenada na lista, que devem ser desalocadas separadamente.
    
    Caso nao exista nenhuma informacao interna a regiao especificada, retorna uma lista vazia.
*/
Lista chavesDentroRetanguloQt(QuadTree quadTree, double x1, double y1, double x2, double y2);

/**
    Similar a funcao chavesDentroRetanguloQt(). Retorna a chave cuja
    coordenada e interna a circunferencia de raio r e centro em (x,y).
 */
Lista chavesDentroCirculoQt(QuadTree quadTree,double x, double y, double r);

/**
    Similar a funcao chavesDentroRetanguloQt().Porem, retorna a coordenada geografica (ponto)
    associada a informacao. Memoria tambem e alocada para cada ponto retornado na lista.
 */
Lista pontosDentroRetanguloQt(QuadTree quadTree,double x1, double y1,double x2, double y2);

/**
    Similar a funcao pontosDentroRetanguloQt(). Retorna pontos internos
    a circunferencia de raio r e centro em (x,y).
 */
Lista pontosDentroCirculoQt(QuadTree quadTree,double x, double y, double r);

/**
    Similar a funcao pontosDentroRetanguloQt(). Retorna apontadores para
    elementos associados aos nodulos da arvore.

    A memoria relativa aos apontadores da lista nao e desalocada.
 */
Lista nosDentroRetanguloQt(QuadTree quadTree,double x1, double y1,double x2, double y2);

/**
    Similar a funcao nosDentroRetanguloQt(). Retorna elementos associados aos nodulos internos
    a circunferencia de raio r e centro em (x,y).
 */
Lista nosDentroCirculoQt(QuadTree quadTree,double x, double y, double r);

/**
    Percorre a arvore em profundidade. Em cada nodulo visitado invoca
    a funcao f. Seja pInfo o valor retornado pela operacao getInfoQt()
    aplicada ao nodulo visitado; a invocacao de f e da forma:

        f(pInfo,ei)
 */
void percorreProfundidadeQt(QuadTree quadTree,funcVisita f,ExtraInfo ei);

/**
    Semelhante a percorreProfundidadeQt. Percorre a arvore em largura.
 */
void percorreLarguraQt(QuadTree quadTree, funcVisita f , ExtraInfo ei);

/**
    Insere na arvore a informacao "pInfo", associada a coordenada referente ao ponto "p".
    Retorna referencia ao nodulo da arvore onde a pInfo foi armazenada.
 */

QtNo insereQt(QuadTree quadTree, ponto p, Info pInfo);

/**
    o nodulo "pNo" a ser removido e marcado como deletado , nao e desalocado, porem nao pode mais ser utilizado.
    "pNo" deve referenciar um no valido dentro da arvore.
    Retorna a informacao contida no nodulo removido.
 */
Info removeQt(QuadTree quadTree, QtNo pNo);

/**
    Retorna uma referencia ao nodulo da arvore associado a coordenada (x,y).
    Retorna NULL, caso nao exista tal nodulo.
 */
QtNo getNoQt_byCoord(QuadTree qt, double x, double y);

/**
    Retorna a raiz da arvore recebida
    Retorna NULL, caso a quadtree nao exista.
 */
QtNo getNoQt_root(QuadTree quadTree);

/**
    Retorna a informacaao armazenada na arvore no nodulo referenciiado por pNo.
    "pNo" deve referenciar um nodulo valido dentro da arvore.
 */
QtInfo getInfoQt(QuadTree quadTree, QtNo pNo);

void desalocaQt2(QuadTree quadTree, void(*freeElements)(void*));

/**
    Libera memoria alocada pela implementacao da arvore. Desaloca apenas memoria alocada por criaQt()) e os
    nodulos da arvore criados por insereQt(). Nao desaloca as listas retornadas nas consultas
    espaciais (_*_DentroRetanguloQt() e _*_DentroCirculoQt(), que devem ser desalocadas separadamente.
    Nao retorna nada.
 */
void desalocaQt(QuadTree quadTree);

/**
    Retorna uma referencia ao nodulo da arvore associado ao id recebido
    Retorna NULL, caso nao exista tal nodulo.
 */
QtNo getNoQt_byId(QuadTree quadTree, char *Id);

/**
    Procura em todas as quadtrees recebidas uma referencia ao nodulo associado ao id recebido
    Retorna NULL, caso nao exista tal nodulo.
 */
QtNo findNodeQt(QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree torresCel, QuadTree semaforos, QuadTree quadras, char *id);

/**
    Retorna o tamanho da quadtree recebida
 */
int getQt_ObjAmount(QuadTree quadTree);

/**
    Cria um array de pontos a partir de uma quadtree, recebendo a array por referencia e o tamanho da array
    sendo recursivamente montada.
    Retorna o tamanho da array.
 */
int quadTreeToArray(QuadTree postos, ponto *array, int tam);

int isCleared(QtNo qNode);

/**
    Retorna o nodulo NE associado ao nodulo recebido, caso exista.
    Caso contrario, retornado NULL
 */
QtNo getNE(QtNo quadTree);

/**
    Retorna o nodulo NW associado ao nodulo recebido, caso exista.
    Caso contrario, retornado NULL
 */
QtNo getNW(QtNo quadTree);

/**
    Retorna o nodulo SE associado ao nodulo recebido, caso exista.
    Caso contrario, retornado NULL
 */
QtNo getSE(QtNo quadTree);

/**
    Retorna o nodulo SW associado ao nodulo recebido, caso exista.
    Caso contrario, retornado NULL
 */
QtNo getSW(QtNo quadTree);

/**
 *  Para fins de balanceamento da arvore, ordena-se a lista de elementos recebida, 
 *  utilizando uma pilha, sendo a lista transformada em quadtree. 
 *  
 *  Nao retorna nada.
 */
void ordenaInsercaoQt(QuadTree quadTree, Lista list);

/**
 *  Faz o rebalanceamento da quadtree recebida, verificando quais elementos estao deletados e assim re-organizando
 *  a quadtree. 
 * 
 *  Nao retorna nada
 */
void recriaQt(QuadTree quadTree);

#endif 
