#include "quadtree.h"
#include "hashTable.h"

typedef void *Grafo;
typedef void *ModuloVertice;

/*
*   cria o grafo
*   necessita do numero de vertices, de uma hashtable e da QuadTree contendo os vertices
*   retorna ponteiro para o grafo
*/
Grafo criaGrafo(int n, HashTable hashTable, QuadTree verticesQt);

/*
*   marca como desativado um certo vertice
*   necessita do objeto vertice 
*   nao retorna nada
*/
void desativarVertice(ModuloVertice vertice);

/*
*   retorna se o vertice esta ativo ou nao
*   necessita do objeto vertice 
*/
int verticeAtivo(ModuloVertice vertice);

/*
*   retorna o vetor de vertices contido no grafo
*   necessita do grafo
*/
Info *retornaVertices(Grafo grafo);

/*
*   retorna o vertice da posicao i contido no vetor de vertices do grafo
*   necessita do grafo e da posicao do vertice no vetor
*/
Info retornaVertice(Grafo grafo, int i);

/*
*   retorna o cep da quadra posicionada do lado direito da aresta recebida
*   necessita das informacoes da aresta
*/
char *retornaLdir(Info infoAresta);

/*
*   retorna o cep da quadra posicionada do lado esquerdo da aresta recebida
*   necessita das informacoes da aresta
*/
char *retornaLesq(Info infoAresta);


/*
*   retorna o nome da aresta recebida
*   necessita das informacoes da aresta
*/
char *retornaNomeRua(Info infoAresta);

/*
*   retorna o Id do vertice inicial da aresta
*   necessita das informacoes da aresta
*/
char *retornaArestaVertInicio(Info infoAresta);

/*
*   retorna o Id do vertice final da aresta
*   necessita das informacoes da aresta
*/
char *retornaArestaVertFim(Info infoAresta);

/*
*   dado um grafo nao direcionado, cria uma arvore geradora minima
*   necessita de um grafo nao direcionado
*   retorna a arvore geradora minima
*/
Grafo primMST(Grafo grafo);

/*
*   encontra a aresta entre 2 vertices recebidos
*   necessita das informacoes de 2 vertices
*   retorna as informacoes da aresta
*/
Info encontrarAresta(Info v1, Info v2);

/*
*   retorna a lista de arestas contida no vertice de posicao 'indice' no vetor de vertices
*   necessita do grafo e da posicao do vertice no vetor de vertices do grafo
*/
Lista retornaListaArestas(Grafo grafo, int indice);

/*
*   retorna objeto ponto contendo as coordenadas do vertice recebido
*   necessita das informacoes do vertice
*/
ponto retornaVerticeCoord(Info v);

/*
*   retorna o Id do vertice recebido
*   necessita das informacoes do vertice
*/
char *retornaVerticeId(Info v);

/*
*   retorna a QuadTree contida no grafo
*   necessita do grafo
*/
QuadTree retornaVerticesQtGrafo(Grafo g);

/*
*   retorna a HashTable contida no grafo
*   necessita do grafo
*/
HashTable retornaHashTableGrafo(Grafo g);

/*
*   cria um vertice com id 'id' e com as coordenadas contidas em 'coord'
*   necessita do grafo
*   retorna o ponteiro para o vertice criado
*/
Info criaVertice(char *id, ponto coord);

/*
*   insere o vertice recebido na posicao 'i' do vetor de vertices contido no grafo recebido
*   necessita do grafo, do vertice e da posicao do vetor a ser inserido o vertice recebido
*   nao retorna nada
*/
void insereVertice(Grafo grafoAtual, int i, Info verticeAtual);

/*  
*   dijkstra encontra os melhores caminhos de um vertice de posicao 'posicaoInicial' no vetor ate os outros vertices
*   necessita do grafo, da posicao do vertice referencial no vetor de vertices, do tipo de trajeto (caminho mais curto/caminho mais rapido) e de um vetor de inteiros
*   retorna a distancia do vertice ate cada outro vertice
*/
double* dijkstra(Grafo grafo, int posInicial, int tipoTrajeto, int *anterior);

/*
*   insere uma aresta na lista de um vertice de posicao 'posicao inicial'
*   necessita do grafo e das informacoes da aresta
*   nao retorna nada
*/
void insereAresta(Grafo grafoAtual, int posInicial, int posFinal, char *ldir, char *lesq, char *nomeRua, double velocidade, double comprimento);

/*
*   retorna o numero de vertices contidos no vetor de vertices do grafo
*   necessita do grafo
*/
int numeroDeVertices(Grafo grafo);

/*
*   faz a construcao de um grafo nao direcionado a partir de um grafo direcionado
*   necessita de um grafo direcionado
*   retorna o grafo nao direcionado
*/
Grafo montaGrafoNaoDirecionado(Grafo grafo);

/*
*   deleta uma aresta
*   necessita do grafo e da id do vertice inicial e final
*   nao retorna nada
*/
void removeAresta(Grafo grafo, char *idV1, char *idV2);

/*
*   deleta o grafo e tudo que esta inserido nele
*   necessita do grafo
*   nao retorna nada
*/
void removeGrafo(Grafo grafo);

/*
*   remove os vertices e arestas mas nao remove a QuadTree nem a HashTable que estao contidas no grafo
*   necessita do grafo
*   nao retorna nada
*/
void removeGrafo_Aux(Grafo grafo);
