#include "grafo.h"
#include "info.h"
#include "lista.h"

#define branco 0
#define amarelo 1
#define vermelho 2
#define inf 3000000.0

typedef struct{
    int ativo;
    ponto coord; 
    Lista arestas; 
    char id[100];
}Vertice;

typedef struct { 
    char inicio[100];
    char fim[100];
    char nomeRua[100];
    char ldir[100];
    char lesq[100];
    double velocidadeMedia;
    double comprimento;
} Aresta;

typedef struct{
    int n;
    HashTable idvXi;
    Vertice **vertices;
    QuadTree verticesQt;
} ObjGrafo;

Grafo criaGrafo(int n, HashTable hashTable, QuadTree verticesQt) {

    ObjGrafo *grafo = (ObjGrafo *) malloc(sizeof(ObjGrafo));
    grafo->n = n;
    grafo->vertices = (Vertice **) malloc(n*sizeof(Vertice));
    grafo->idvXi = hashTable;
    grafo->verticesQt = verticesQt;

    return grafo;
}

Info encontrarArestaEmGrafo(Grafo grafo, Info v1, Info v2){
    
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;

    Vertice *vertice1 = (Vertice*) v1;
    Vertice *vertice2 = (Vertice*) v2;

    int *posicao1 = getModulo(searchHash(grafoAtual->idvXi, vertice1->id));
    //printf("posicao = %d\n", *posicao1);

    Lista arestas = grafoAtual->vertices[*posicao1]->arestas;
    nodulo noduloAresta = getFirst(arestas);
    Aresta *aresta;

    while(noduloAresta!=NULL){

        aresta = getInfo(noduloAresta);

        if(strcmp(aresta->fim, vertice2->id)==0){
            return aresta;
        }

        noduloAresta = getNext(noduloAresta);
    }

    return NULL;
}

Info encontrarAresta(Info v1, Info v2){
    
    Vertice *vertice1 = (Vertice*) v1;
    Vertice *vertice2 = (Vertice*) v2;
    Lista arestas = vertice1->arestas;

    nodulo noduloAresta = getFirst(arestas);

    while(noduloAresta!=NULL){

        Aresta *aresta = getInfo(noduloAresta);

        if(strcmp(aresta->fim, vertice2->id)==0){
            return aresta;
        }

        noduloAresta = getNext(noduloAresta);
    }

    return NULL;
}

//marca como deletado
void desativarVertice(ModuloVertice vertice){
    Vertice *v = (Vertice*) vertice;
    v->ativo = 0;
}

int verticeAtivo(ModuloVertice vertice){
    Vertice *v = (Vertice*) vertice;
    return v->ativo;
}

Info *retornaVertices(Grafo grafo){
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    return (Info*)grafoAtual->vertices;
}

Info retornaVertice(Grafo grafo, int i){
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    return grafoAtual->vertices[i];
}

char *retornaLdir(Info infoAresta){
    Aresta *aresta = (Aresta*) infoAresta;
    return aresta->ldir;
}

char *retornaLesq(Info infoAresta){
    Aresta *aresta = (Aresta*) infoAresta;
    return aresta->lesq;
}

char *retornaNomeRua(Info infoAresta){
    Aresta *aresta = (Aresta*) infoAresta;
    return aresta->nomeRua;
}

char *retornaArestaVertInicio(Info infoAresta){
    Aresta *aresta = (Aresta*) infoAresta;
    return aresta->inicio;
}

char *retornaArestaVertFim(Info infoAresta){
    Aresta *aresta = (Aresta*) infoAresta;
    return aresta->fim;
}

Lista retornaListaArestas(Grafo grafo, int indice){
    
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    return grafoAtual->vertices[indice]->arestas;
}

int numeroDeVertices(Grafo grafo){
    
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    return grafoAtual->n;
}

ponto retornaVerticeCoord(Info v){
    Vertice* vertice = (Vertice*) v;
    return vertice->coord;
}

char *retornaVerticeId(Info v){
    Vertice* vertice = (Vertice*) v;
    return vertice->id;
}

QuadTree retornaVerticesQtGrafo(Grafo g){
    ObjGrafo* grafo = (ObjGrafo*) g;
    return grafo->verticesQt;
}

HashTable retornaHashTableGrafo(Grafo g){
    ObjGrafo* grafo = (ObjGrafo*) g;
    return grafo->idvXi;
}

Info criaVertice(char *id, ponto coord){

    Vertice *vertice = malloc (sizeof(Vertice));
    strcpy(vertice->id, id);
    vertice->coord = coord;
    vertice->ativo = 1; //vertice ativo

    return vertice;
}

int calcularMenorDistancia(Grafo grafo, double *distancia, int *aberto){
    
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    int i, menorDistancia;
    
    for(i = 0; i < grafoAtual->n; i++) {
        if(aberto[i]==1)
            break;
    }
    
    if(i == grafoAtual->n)
        return -1;
    
    menorDistancia = i;

    for(i = i+1; i < grafoAtual->n; i++) {
        if(aberto[i] && distancia[menorDistancia] > distancia[i])
            menorDistancia = i;
    }

    return menorDistancia;
}

Aresta *criaAresta(char *verticeInicial, char *verticeFinal, char *nomeRua, char *ldir, char *lesq, double velocidade, double comprimento){
    
    Aresta *aresta = (Aresta *) malloc (sizeof(Aresta));

    strcpy(aresta->inicio, verticeInicial);
    strcpy(aresta->fim, verticeFinal);
    strcpy(aresta->ldir, ldir);
    strcpy(aresta->lesq, lesq);
    strcpy(aresta->nomeRua, nomeRua);
    aresta->comprimento = comprimento;
    aresta->velocidadeMedia = velocidade;

    return aresta;
}

void insereVertice(Grafo grafoAtual, int i, Info verticeAtual){
    
    ObjGrafo *grafo = (ObjGrafo*) grafoAtual;

    if(!grafoAtual){
        return;
    }

    grafo->vertices[i] = verticeAtual;
    grafo->vertices[i]->arestas = criarLista();
}

void insereAresta(Grafo grafoAtual, int posInicial, int posFinal, char *ldir, char *lesq, char *nomeRua, double velocidade, double comprimento){

    ObjGrafo *grafo = (ObjGrafo*) grafoAtual;

    if(!grafo){
        return;
    }
    
    Aresta *aresta = criaAresta(grafo->vertices[posInicial]->id, grafo->vertices[posFinal]->id, nomeRua, ldir, lesq, velocidade, comprimento);
    insertAfterLast(grafo->vertices[posInicial]->arestas , aresta);
}

void relaxa(Grafo grafo, int posicaoInicial, int posicaoProx, int* anterior, double* distancia, int tipoTrajeto){
    
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    
    Lista arestas = grafoAtual->vertices[posicaoInicial]->arestas;
    nodulo noduloAresta = getFirst(arestas);

    Aresta* aresta = getInfo(getFirst(arestas));
    int *posicaoVertice = getModulo(searchHash(grafoAtual->idvXi, aresta->fim));

    while(noduloAresta && *posicaoVertice != posicaoProx){

        noduloAresta = getNext(noduloAresta);
        if(noduloAresta == NULL){
            return;
        }
        aresta = getInfo(noduloAresta);
        posicaoVertice = getModulo(searchHash(grafoAtual->idvXi, aresta->fim));
    } 

    if(aresta) {
        
        double peso;
        
        if(tipoTrajeto == 1){
            if(aresta->comprimento==0 && aresta->velocidadeMedia==0){
                peso=0;
            }else{
                peso = aresta->comprimento/aresta->velocidadeMedia;
            }
        }else{
            peso = aresta->comprimento;
        }

        if(distancia[posicaoProx] > distancia[posicaoInicial] + peso) {
            distancia[posicaoProx] = distancia[posicaoInicial] + peso;
            anterior[posicaoProx] = posicaoInicial;
        }
    }

}

void comecaDijkstra(Grafo grafo, int *anterior, int posInicial, double *distancia){
    
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;

    for(int i = 0; i < grafoAtual->n; i++) {
        distancia[i] = inf;
        anterior[i] = -1;
    }

    distancia[posInicial] = 0.0;
}

int existeAberto(Grafo grafo, int* aberto) {

    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;

    for(int i = 0; i < grafoAtual->n; i++) {

        if(aberto[i]){
            return 1; //true
        }

    }
    
    return 0; //false
}

double* dijkstra(Grafo grafo, int posInicial, int tipoTrajeto, int *anterior){

    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    double* distancia = (double*) malloc(grafoAtual->n * sizeof(double));
    int menor, aberto[grafoAtual->n];

    Lista arestas;

    comecaDijkstra(grafoAtual, anterior, posInicial, distancia);

    for(int i = 0; i < grafoAtual->n; i++){
        aberto[i] = 1; 
    } 

    while (existeAberto(grafo, aberto) == 1){

        menor = calcularMenorDistancia(grafo, distancia, aberto);
        aberto[menor] = 0;

        Lista arestas = grafoAtual->vertices[menor]->arestas;
        nodulo noduloAresta = getFirst(arestas);

        while(noduloAresta!=NULL) {

            Aresta *aresta = getInfo(noduloAresta);

            int *posicaoFim = getModulo(searchHash(grafoAtual->idvXi, aresta->fim));
            int *posicaoInicio = getModulo(searchHash(grafoAtual->idvXi, aresta->inicio));
            
            if(grafoAtual->vertices[*posicaoInicio]->ativo==1 && grafoAtual->vertices[*posicaoFim]->ativo==1){
                relaxa(grafoAtual, menor, *posicaoFim, anterior, distancia, tipoTrajeto);
            }

            noduloAresta = getNext(noduloAresta);
        }

    }

    return distancia; 

}

void printDistancia(Grafo grafo, int *anterior, int inicio, int *distancia){

    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;

    for(int i=0;i< grafoAtual->n;i++){
        printf("Trajeto %s - %s: %d\n", grafoAtual->vertices[inicio]->id, grafoAtual->vertices[i]->id, distancia[i]);
    }
}

void imprimeGrafo(Grafo grafo) {
    
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;

    if (grafoAtual == NULL) {
        printf("Grafo vazio!\n");
       return;
    }

    printf("Vertices: %d\n", grafoAtual->n);

    for(int i = 0; i < grafoAtual->n; i++) {
        
        printf("%s: ", grafoAtual->vertices[i]->id);

        Lista arestas = grafoAtual->vertices[i]->arestas;
        nodulo noduloAresta = getFirst(arestas);

        while(noduloAresta!=NULL) {
            Aresta *aresta = getInfo(noduloAresta); 
            printf("%s ", aresta->fim);
            noduloAresta = getNext(noduloAresta); 
        }

        printf("\n");    
    }

}

void limparListaArestas(Lista lista){

    nodulo node = getFirst(lista);

    while(node!=NULL){

        nodulo aux = getNext(node);

        Info infoAresta = getInfo(node);
        Aresta *aresta = (Aresta*) infoAresta;

        free(aresta);
        removeNode(node, lista);
   
        node = aux;
    }

    free(lista);
}

Grafo montaGrafoNaoDirecionado(Grafo grafo){

    ObjGrafo *grafoAtual = (ObjGrafo *) grafo;
    HashTable idvXi = grafoAtual->idvXi;  //hashtable n pode ser deletada aqui!!!!
    ObjGrafo *grafoNaoDirecionado = criaGrafo(grafoAtual->n, idvXi, NULL);

    for(int i=0;i< grafoAtual -> n ; i++){

        Vertice *v1 = grafoAtual->vertices[i];
        ponto novaCoord = montaPonto(retornaPonto_X(v1->coord), retornaPonto_Y(v1->coord));
        Vertice *novoVertice = criaVertice(v1->id,novaCoord);

        insereVertice(grafoNaoDirecionado, i, novoVertice);
    }

    for(int i=0;i < grafoAtual->n; i++){

        Vertice *v1 = grafoAtual->vertices[i];
        int *posicaoV1 = getModulo(searchHash(grafoAtual->idvXi,v1->id));

        Lista arestas = v1->arestas;
        nodulo noduloAresta = getFirst(arestas);

        while(noduloAresta){
            
            Aresta *aresta = getInfo(noduloAresta);
            int *posicaoV2 = getModulo(searchHash(grafoAtual->idvXi, aresta->fim));
            
            if(encontrarArestaEmGrafo(grafoNaoDirecionado, v1 , grafoAtual->vertices[*posicaoV2])==NULL){
                insereAresta(grafoNaoDirecionado, *posicaoV1, *posicaoV2, aresta->ldir, aresta-> lesq, aresta->nomeRua, aresta->velocidadeMedia, aresta->comprimento);
            }

            if(encontrarArestaEmGrafo(grafoNaoDirecionado, grafoAtual->vertices[*posicaoV2], v1)==NULL){
                insereAresta(grafoNaoDirecionado, *posicaoV2, *posicaoV1, aresta->ldir, aresta-> lesq, aresta->nomeRua, aresta->velocidadeMedia, aresta->comprimento);
            }
            
            noduloAresta = getNext(noduloAresta);
        }
    }

    return grafoNaoDirecionado;
}

void removeVertice(Info vertice){
    Vertice *v = (Vertice*) vertice; 
    limparListaArestas(v->arestas);
    removePonto(v->coord);
    free(v);
}

void removeGrafo_Aux(Grafo grafo){

    if(grafo==NULL)
        return;

    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    
    for(int i=0; i< grafoAtual->n; i++){
        removeVertice(grafoAtual->vertices[i]);
    }

    free(grafoAtual->vertices);
    free(grafoAtual);
}


void removeGrafo(Grafo grafo){

    if(grafo==NULL)
        return;

    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;

    desalocaHT_del(grafoAtual->idvXi);
    desalocaQt(grafoAtual->verticesQt);
    
    for(int i=0; i< grafoAtual->n; i++){
        removeVertice(grafoAtual->vertices[i]);
    }

    free(grafoAtual->vertices);
    free(grafoAtual);
}

int menorDistancia(Grafo grafo, int *aberto, int *distancia)
{
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    int i, menor;

    for (i = 0; i < grafoAtual->n; i++)
    {
        if (aberto[i])
            break;
    }

    if (i == grafoAtual->n)
        return -1;

    menor = i;

    for (i = i + 1; i < grafoAtual->n; i++)
    {
        if (aberto[i] && distancia[menor] > distancia[i])
            menor = i;
    }
    return menor;
}

Grafo retornaArvoreGeradoraMin(Grafo grafo, int *anterior, double *pesos, int n)
{
    ObjGrafo* grafoAtual = (ObjGrafo*) grafo;
    HashTable idvXi = grafoAtual->idvXi;
    ObjGrafo* arvoreGeradoraMinima = criaGrafo(n, idvXi, grafoAtual->verticesQt);

    for(int i=0;i< grafoAtual -> n ; i++){

        Vertice *v1 = grafoAtual->vertices[i];
        ponto novaCoord = montaPonto(retornaPonto_X(v1->coord), retornaPonto_Y(v1->coord));
        Vertice *novoVertice = criaVertice(v1->id,novaCoord);

        insereVertice(arvoreGeradoraMinima, i, novoVertice);
    }
    
    for(int i=1; i<n; i++){
        if(anterior[i]==-1){
            continue;
        }
        Vertice *v1 = grafoAtual->vertices[anterior[i]];
        Vertice *v2 = grafoAtual->vertices[i];
        Aresta *aresta = encontrarArestaEmGrafo(grafoAtual, v1, v2);
        insereAresta(arvoreGeradoraMinima, anterior[i], i, aresta->ldir, aresta->lesq, aresta->nomeRua, aresta->velocidadeMedia, aresta->comprimento);
        insereAresta(arvoreGeradoraMinima, i, anterior[i], aresta->ldir, aresta->lesq, aresta->nomeRua, aresta->velocidadeMedia, aresta->comprimento);
    }

    return arvoreGeradoraMinima;
}

void removeAresta(Grafo grafo, char *idV1, char *idV2){
    
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;

    int *posicaoV1 = getModulo(searchHash(grafoAtual->idvXi, idV1));
    int *posicaoV2 = getModulo(searchHash(grafoAtual->idvXi, idV2));

    Vertice *V1 = grafoAtual->vertices[*posicaoV1];
    Vertice *V2 = grafoAtual->vertices[*posicaoV2];

    Lista arestas = V1->arestas;

    nodulo noduloAresta = getFirst(arestas);

    while(noduloAresta){

        Aresta *aresta = getInfo(noduloAresta);

        if(strcmp(idV2, aresta->fim)==0){
            break;
        }

        noduloAresta = getNext(noduloAresta);
    }

    if(noduloAresta){
        Info aresta = removeNode(noduloAresta, arestas);
        free(aresta);
    }

}

Grafo primMST(Grafo grafo)
{
    ObjGrafo *grafoAtual = (ObjGrafo*) grafo;
    int N = grafoAtual->n;
    int anterior[N];
    double chave[N];
    int mstSet[N];
    Aresta *aresta;

    for (int i = 0; i < N; i++)
        chave[i] = inf, mstSet[i] = 1, anterior[i] = -1; 

    chave[0] = 0;
    anterior[0] = -1; 

    for (int i = 0; i < N - 1; i++)
    {

        int u = calcularMenorDistancia(grafo,chave, mstSet);
        mstSet[u] = 0;

        Lista arestas = grafoAtual->vertices[u]->arestas; 
        nodulo noduloAresta = getFirst(arestas);

        while (noduloAresta)
        {
            Aresta *aresta = getInfo(noduloAresta);
            int *posicao = getModulo(searchHash(grafoAtual->idvXi, aresta->fim));
            double peso = aresta->comprimento;            

            if (mstSet[*posicao] == 1 && peso < chave[*posicao])
            {
                anterior[*posicao] = u;
                chave[*posicao] = peso;
            }

            noduloAresta = getNext(noduloAresta);
        }

    }

    return retornaArvoreGeradoraMin(grafo, anterior, chave, N);
}
