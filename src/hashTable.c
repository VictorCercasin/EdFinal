#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashTable.h"

typedef struct HashT {
      int numEntradas;
      Lista *itens; 
}hash_table;

HashTable criaHt(int numEntradas){

        if(numEntradas>0){

                hash_table* hashTable = (hash_table *) malloc(sizeof(hash_table));
                hashTable->numEntradas = numEntradas;

                hashTable->itens = criarVetorLista(numEntradas);

                for(int i=0;i<numEntradas;i++){
                        hashTable->itens[i] = criarLista();
                }

                return hashTable;
        }

        return NULL;
}

void removeItens(HashTable ht){
        hash_table *hashTable = (hash_table*) ht;
        free(hashTable->itens);
}

Lista listaItensHt_lista(HashTable ht, int indice){

        hash_table *hashTable = (hash_table*) ht;
        return hashTable->itens[indice];
}

int numEntradasHt(HashTable ht){

        hash_table *hashTable = (hash_table*) ht;
        return hashTable->numEntradas;
}

int funcHash(char *chave, int numEntradas){

        int i=0;

        for(int j=0;chave[j];j++){
                i+=chave[j];
        }

        return i % numEntradas;
}

void *searchHash(HashTable hashTable, char *str){

        hash_table *ht = (hash_table*) hashTable;
        

        int i = funcHash(str, ht->numEntradas);
        Lista list = ht->itens[i];

        nodulo node = findNode(list,str);

        if(node!=NULL){
                return getInfo(node);
        }

        return NULL;
}

void insereHT(HashTable hashTable, char *chave, void *item){

        hash_table *ht = (hash_table*) hashTable;

        int *teste = item;

        int indice_hash = funcHash(chave,ht->numEntradas);
        Lista list = ht->itens[indice_hash];

        insertAfterLast(list, item);
}

void *removeHT(HashTable hashTable, char *chave){
        hash_table *ht = (hash_table*) hashTable;

        int indice_hash = funcHash(chave,ht->numEntradas);
        Lista list = ht->itens[indice_hash];

        nodulo node = findNode(list, chave);
        if(node == NULL) return NULL;

        Info info = removeNode(node, list);

        return info;
}

void desalocaHT(HashTable hashTable){

        hash_table *ht = (hash_table*) hashTable;

        for(int i=0;i<ht->numEntradas;i++){

                Lista list = ht->itens[i];
                nodulo node = getFirst(list);

                while(node!=NULL){
                     nodulo aux = getNext(node);
                     removeNode(node,list);
                     
                     node = aux;
                }

                free(list);
        }

        free(ht->itens);
        free(hashTable);
}

void desalocaHT_del(HashTable hashTable){

        hash_table *ht = (hash_table*) hashTable;

        for(int i=0;i<ht->numEntradas;i++){

                Lista list = ht->itens[i];
                nodulo node = getFirst(list);

                while(node!=NULL){
                        nodulo aux = getNext(node);
                        Info info = removeNode(node,list);
                        removeInfo(info);
                        node = aux;
                }

                free(list);
        }

        free(ht->itens);
        free(hashTable);
}

