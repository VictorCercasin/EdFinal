#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

typedef struct Node
{
    Info info;
    struct Node *anterior;
    struct Node *proximo;
} no;

typedef struct L {
    no *primeiro;
    no *ultimo;
    int size;
} list;


int transfStringInt(char *dado){
        
    int aux;
        
    sscanf(dado,"%d",&aux);

    return aux;
}

double transfStringDouble(char *dado){
	
    double aux;

	sscanf(dado,"%lf",&aux);

	return aux;
}

nodulo getNext(nodulo elemento){
    no* node = (no*) elemento;    

    return node->proximo;
}

nodulo getFirst(Lista lista){
    
    list* l = (list*) lista;

    return l->primeiro;
}

nodulo getLast(Lista lista){
    
    list* l = (list*) lista;
    if(l->size == 0) return NULL;
    return l->ultimo;
}

Info getInfo(nodulo elemento){
    
    no* node = (no*) elemento;

    return node->info;
}

nodulo getPrevious(nodulo elemento){

    no* node = (no*) elemento;

    return node->anterior;
}

Lista criarLista(){

    list* lista = (list *) malloc(sizeof(list));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->size = 0;
    return lista; 
}

Info removeNode(nodulo node, Lista listagem){

    no* element = (no*) node;
    list* lista = (list*) listagem;

    if(element->anterior == NULL){

        if(element->proximo!=NULL){
            element->proximo->anterior = NULL;
            lista->primeiro = element->proximo;

        }else{
            lista->primeiro = NULL;
            lista->ultimo = NULL;
        }

    }

    else if(element->proximo==NULL){

        element->anterior->proximo = NULL;
        lista->ultimo = element->anterior;

    }

    else{

        element->anterior->proximo = element->proximo;
        element->proximo->anterior = element->anterior;
    
    }

    Info info = element->info;

    free(element);
    lista->size--;
    return info;
}

Info removeFirst(Lista listagem){
    
    list* lista = (list*) listagem;
    no* elemento = lista->primeiro;

    if(lista->primeiro == NULL){
        return NULL;
    }
    if(lista->primeiro == lista->ultimo){
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }else{
        lista->primeiro = elemento->proximo;
        lista->primeiro->anterior = NULL;
    }

    Info info = elemento->info;
    free(elemento);
    lista->size--;
    return info;
}

Info removeLast(Lista listagem){
    
    list* lista = (list*) listagem;
    no* elemento = lista->ultimo;

    if(lista->ultimo == NULL){
        return NULL;
    }
    if(lista->ultimo == lista->primeiro){
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }else{
        lista->ultimo = elemento->anterior;
        lista->ultimo->proximo = NULL;
    }

    Info info = elemento->info;
    free(elemento);
    lista->size--;
    return info;
}

void removerElemento(Lista listagem, nodulo elemento){

    Info info = getInfo(elemento);

    removeInfo(info);
    removeNode(elemento, listagem);
}

void insertBefore(nodulo nodeProx, Info info, Lista listagem){

    list* lista = (list*) listagem;
   
    no* node = (no*) malloc(sizeof(no));
    no* nProx = (no*) nodeProx;

    node->info = info;

    no* first = lista->primeiro;

    if(nProx == first){

        first->anterior = node;
        node->proximo = first;

        lista->primeiro = node;
    }else{

        no* aux = nProx->anterior;
        aux->proximo = node;
        nProx->anterior = node;
        node->proximo = nProx;
        node->anterior = nProx->anterior;
    }
    lista->size++;
    return;
}

void insertAfter(nodulo nodeAnt, Info info, Lista listagem){

    list* lista = (list*) listagem;
   
    no* node = (no*) malloc(sizeof(no));
    no* nAnt = (no*) nodeAnt;

    node->info = info;

    no* last = lista->ultimo;

    if(nAnt == last){

        last->proximo = node;
        node->proximo = NULL;
        node->anterior = last;

        lista->ultimo = node;
    }else{

        no* aux = nAnt->proximo;
        nAnt->proximo = node;
        node->proximo = NULL;
        node->anterior = nAnt;
    }


    lista->size++;
    return;
}

void insertAfterLast(Lista listagem, Info info){

    list* lista = (list*) listagem;
   
    no* node = (no*) malloc(sizeof(no));

    node->info = info;
    
    if(lista->primeiro == NULL){
        lista->primeiro = node;
        lista->ultimo = node;
        node->anterior = NULL;
        node->proximo = NULL;
        lista->size++;
        return;
    }

    no* last = lista->ultimo;

    last->proximo = node;
    node->proximo = NULL;
    node->anterior = last;

    lista->ultimo = node;
    
    lista->size++;
    return;
}

void limparLista(Lista listagem){

    nodulo node = getFirst(listagem);
    list* lista = (list*) listagem;

    while(node!=NULL){

        nodulo aux = getNext(node);
        removerElemento(listagem, node);

        node = aux;
    }

    free(lista);
}


void limparMemoria(Lista figuras, Lista hidrantes, Lista semaforos, Lista quadras, Lista torresCel, Lista listQRY, Lista pontos, Lista regioes, Lista casas, Lista poligonos){

    limparLista(figuras);
    limparLista(hidrantes);
    limparLista(semaforos);
    limparLista(quadras);
    limparLista(torresCel);
    limparLista(listQRY);
    limparLista(pontos);
    limparLista(regioes);
    limparLista(casas);
    limparLista(poligonos);
}

nodulo searchNode(Lista hidrantes, Lista semaforos, Lista quadras, Lista torresCel, char *id){

    nodulo node = NULL;

    node = findNode(semaforos, id);

    if(node != NULL){
        return node;
    }

    node = findNode(quadras, id);

    if(node != NULL){
        return node;
    }

    node = findNode(torresCel, id);

    if(node != NULL){
        return node;
    }

    node = findNode(hidrantes, id);

    return node;
}

nodulo findNode_byInfo(Lista listagem, Info info){
    list* lista = (list*) listagem;

    no *elemento = getFirst(lista);

    while(elemento != NULL){

        if(info == elemento->info){
            break;
        }

        elemento = getNext(elemento);  
    }

    return elemento;

}

nodulo findNode(Lista listagem, char *id){
    list* lista = (list*) listagem;

    nodulo elemento = getFirst(lista);
    Info info;

    while(elemento != NULL){

        info = getInfo(elemento);

        if(strcmp(retornaPos(info),id)==0){
            break;
        }

        elemento = getNext(elemento);  
    }

    return elemento;

}

int listSize(Lista listagem){
    list* lista = (list*) listagem;
    return lista->size;
}

void *criarVetorLista(int n){

    void *array_Lista = malloc(n*sizeof(list));

    return array_Lista;
}

Lista searchLista(Lista figuras, Lista hidrantes, Lista semaforos, Lista quadras, Lista torresCel, char *id){
    nodulo node = NULL;
    node = findNode(figuras, id);

    if(node != NULL){
        return figuras;
    }

    node = findNode(semaforos, id);

    if(node != NULL){
        return semaforos;
    }

    node = findNode(quadras, id);

    if(node != NULL){
        return quadras;
    }

    node = findNode(torresCel, id);

    if(node != NULL){
        return torresCel;
    }

    node = findNode(hidrantes, id);

    return hidrantes;
}

void limparLista_aux(Lista listagem){

    nodulo node = getFirst(listagem);
    list* lista = (list*) listagem;

    while(node!=NULL){

        nodulo aux = getNext(node);
        removeNode(node,lista);

        node = aux;
    }

    free(lista);
}
