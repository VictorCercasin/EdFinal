#include "quadtree.h"
#include "leqry.h"

typedef struct qtNode{

    ponto coord;
    Info info;
    
    int cleared;

    struct qtNode *nw;
    struct qtNode *ne;
    struct qtNode *sw;
    struct qtNode *se; 

}quadNode;

typedef struct qt{  
    quadNode *raiz;
    int tamanho;
    char*(*getId)(void*);
} quadtree;

quadNode *criaQuadNode(Info info, ponto coord){
    
    quadNode *no = malloc(sizeof(quadNode));
    
    no->info = info;
    no->coord = coord;

    no->cleared = 0;

    no->nw = NULL;
    no->ne = NULL;
    no->sw = NULL;
    no->se = NULL;

    return no;
}

QuadTree criaQt(funcGetChave f){

    quadtree *qt =  (quadtree*) malloc(sizeof(quadtree));
    
    qt->raiz = NULL;
    qt->tamanho = 0;
    qt->getId = f;

    return qt;
}

void chavesDentroRetanguloQt_aux(quadNode *qNode, char*(*getId)(void*), Lista list, double x1, double y1, double x2, double y2){
    
    if(qNode == NULL){
        return;
    }

    Info info = getInfoQt(NULL,qNode);
    Modulo objeto = getModulo(info);
    ponto pnt = retornaInfoCoord(info);

    if(verificaInteriorRet(x1, y1, x2, y2, info)==0 && qNode->cleared==0){

        String chave = montaString(getId(objeto));
        Info infoChave = montaInfo("str","null",chave);
        insertAfterLast(list, infoChave);

        chavesDentroRetanguloQt_aux(qNode->se, getId, list, x1, y1, x2, y2);
        chavesDentroRetanguloQt_aux(qNode->ne, getId, list, x1, y1, x2, y2);
        chavesDentroRetanguloQt_aux(qNode->sw, getId, list, x1, y1, x2, y2); 
        chavesDentroRetanguloQt_aux(qNode->nw, getId, list, x1, y1, x2, y2);

    }else{

        //checa se o elemento esta nos cantos ao redor do retangulo
        if(retornaPonto_Y(pnt) < y1 && retornaPonto_X(pnt) > x2) chavesDentroRetanguloQt_aux(qNode->ne, getId, list, x1, y1, x2, y2);
        else if(retornaPonto_Y(pnt) < y1 && retornaPonto_X(pnt) < x1) chavesDentroRetanguloQt_aux(qNode->nw, getId, list, x1, y1, x2, y2);
        else if(retornaPonto_Y(pnt) > y2 && retornaPonto_X(pnt) < x1) chavesDentroRetanguloQt_aux(qNode->sw, getId, list, x1, y1, x2, y2);
        else if(retornaPonto_Y(pnt) > y2 && retornaPonto_X(pnt) > x2) chavesDentroRetanguloQt_aux(qNode->se, getId, list, x1, y1, x2, y2);
            
        //checa se o elemento esta acima do retangulo (verifica somente ne e nw)
        else if(retornaPonto_Y(pnt) < y1){
            chavesDentroRetanguloQt_aux(qNode->ne, getId, list, x1, y1, x2, y2);
            chavesDentroRetanguloQt_aux(qNode->nw, getId, list, x1, y1, x2, y2);
        }
            
        //checa se o elemento esta abaixo do retangulo (verifica somente se e sw)
        else if(retornaPonto_Y(pnt) > y2){
            chavesDentroRetanguloQt_aux(qNode->se, getId, list, x1, y1, x2, y2);
            chavesDentroRetanguloQt_aux(qNode->sw, getId, list, x1, y1, x2, y2);
        }

        //checa se o elemento esta do lado esquerdo do retangulo (verifica somente sw e nw)
        else if(retornaPonto_X(pnt) < x1){
            chavesDentroRetanguloQt_aux(qNode->sw, getId, list, x1, y1, x2, y2);
            chavesDentroRetanguloQt_aux(qNode->nw, getId, list, x1, y1, x2, y2);
        }

        //checa se o elemento esta do lado direito do retangulo (verifica somente se e ne)
        else if(retornaPonto_X(pnt) > x2){
            chavesDentroRetanguloQt_aux(qNode->se, getId, list, x1, y1, x2, y2);
            chavesDentroRetanguloQt_aux(qNode->ne, getId, list, x1, y1, x2, y2);
        }

        else{
            chavesDentroRetanguloQt_aux(qNode->se, getId, list, x1, y1, x2, y2);
            chavesDentroRetanguloQt_aux(qNode->ne, getId, list, x1, y1, x2, y2);
            chavesDentroRetanguloQt_aux(qNode->sw, getId, list, x1, y1, x2, y2); 
            chavesDentroRetanguloQt_aux(qNode->nw, getId, list, x1, y1, x2, y2);
        }

    }

}

Lista chavesDentroRetanguloQt(QuadTree quadTree, double x1, double y1, double x2, double y2){
    
    quadtree* qt = (quadtree*) quadTree;

    if(qt == NULL){
        return NULL;
    }
    
    Lista list = criarLista();
    chavesDentroRetanguloQt_aux(qt->raiz, qt->getId , list, x1, y1, x2, y2);

    return list;
}

void chavesDentroCirculoQt_aux(quadNode *qNode, char*(*getId)(void*), Lista list, double x, double y, double r){
    
    if(qNode == NULL){
        return;
    }

    Info info = getInfoQt(NULL,qNode);
    Modulo objeto = getModulo(info);
    ponto pnt = retornaInfoCoord(info);

    if(verificaInteriorCirc(x,y,r,info)==0 && qNode->cleared==0){

        String chave = montaString(getId(objeto));
        Info infoChave = montaInfo("str","null",chave);
        insertAfterLast(list, infoChave);

        chavesDentroCirculoQt_aux(qNode->se, getId, list, x, y, r);
        chavesDentroCirculoQt_aux(qNode->ne, getId, list, x, y, r);
        chavesDentroCirculoQt_aux(qNode->sw, getId, list, x, y, r); 
        chavesDentroCirculoQt_aux(qNode->nw, getId, list, x, y, r);
        
    }else{

        if(retornaPonto_Y(pnt) < y-r && retornaPonto_X(pnt) > x+r) chavesDentroCirculoQt_aux(qNode->ne, getId, list, x, y, r);
        else if(retornaPonto_Y(pnt) < y-r && retornaPonto_X(pnt) < x-r) chavesDentroCirculoQt_aux(qNode->nw, getId, list, x, y, r);
        else if(retornaPonto_Y(pnt) > y+r && retornaPonto_X(pnt) < x-r) chavesDentroCirculoQt_aux(qNode->sw, getId, list, x, y, r);
        else if(retornaPonto_Y(pnt) > y+r && retornaPonto_X(pnt) > x+r) chavesDentroCirculoQt_aux(qNode->se, getId, list, x, y, r);

        //checa se o elemento esta acima do circulo (verifica somente ne e nw)
        else if(retornaPonto_Y(pnt) < y-r){
            chavesDentroCirculoQt_aux(qNode->ne, getId, list, x, y, r);
            chavesDentroCirculoQt_aux(qNode->nw, getId, list, x, y, r);
        }

        //checa se o elemento esta abaixo do circulo (verifica somente se e sw)
        else if(retornaPonto_Y(pnt) > y+r){
            chavesDentroCirculoQt_aux(qNode->se, getId, list, x, y, r);
            chavesDentroCirculoQt_aux(qNode->sw, getId, list, x, y, r);
        }

        //checa se o elemento esta do lado esquerdo do circulo (verifica somente sw e nw)
        else if(retornaPonto_X(pnt) < x-r){
            chavesDentroCirculoQt_aux(qNode->sw, getId, list, x, y, r);
            chavesDentroCirculoQt_aux(qNode->nw, getId, list, x, y, r);
        }

        //checa se o elemento esta do lado direito do circulo (verifica somente se e ne)
        else if(retornaPonto_X(pnt) > x+r){
            chavesDentroCirculoQt_aux(qNode->se, getId, list, x, y, r);
            chavesDentroCirculoQt_aux(qNode->ne, getId, list, x, y, r);
        }

        else{
            chavesDentroCirculoQt_aux(qNode->se, getId, list, x, y, r);
            chavesDentroCirculoQt_aux(qNode->ne, getId, list, x, y, r);
            chavesDentroCirculoQt_aux(qNode->sw, getId, list, x, y, r); 
            chavesDentroCirculoQt_aux(qNode->nw, getId, list, x, y, r);
        }
    }

}

Lista chavesDentroCirculoQt(QuadTree quadTree,double x, double y, double r){

    quadtree* qt = (quadtree*) quadTree;

    if(qt == NULL){
        return NULL;
    }
    
    Lista list = criarLista();
    chavesDentroCirculoQt_aux(qt->raiz, qt->getId , list, x, y, r);

    return list;
}

void pontosDentroRetanguloQt_aux(quadNode *qNode, Lista list, double x1, double y1, double x2, double y2){

    if(qNode == NULL){
        return;
    }

    Info info = getInfoQt(NULL,qNode);
    ponto pnt = retornaInfoCoord(info);

    if(verificaInteriorRet(x1, y1, x2, y2, info)==0 && qNode->cleared==0){

        ponto novoPonto = montaPonto(retornaPonto_X(pnt),retornaPonto_Y(pnt));
        Info infoPonto = montaInfo("ps","null",novoPonto);
        insertAfterLast(list, infoPonto);

        pontosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
        pontosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
        pontosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2); 
        pontosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);

    }else{

        //checa se o elemento esta nos cantos ao redor do retangulo
        if(retornaPonto_Y(pnt) < y1 && retornaPonto_X(pnt) > x2) pontosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
        else if(retornaPonto_Y(pnt) < y1 && retornaPonto_X(pnt) < x1) pontosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);
        else if(retornaPonto_Y(pnt) > y2 && retornaPonto_X(pnt) < x1) pontosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2);
        else if(retornaPonto_Y(pnt) > y2 && retornaPonto_X(pnt) > x2) pontosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
            
        //checa se o elemento esta acima do retangulo (verifica somente ne e nw)
        else if(retornaPonto_Y(pnt) < y1){
            pontosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
            pontosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);
        }
            
        //checa se o elemento esta abaixo do retangulo (verifica somente se e sw)
        else if(retornaPonto_Y(pnt) > y2){
            pontosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
            pontosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2);
        }

        //checa se o elemento esta do lado esquerdo do retangulo (verifica somente sw e nw)
        else if(retornaPonto_X(pnt) < x1){
            pontosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2);
            pontosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);
        }

        //checa se o elemento esta do lado direito do retangulo (verifica somente se e ne)
        else if(retornaPonto_X(pnt) > x2){
            pontosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
            pontosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
        }

        else{
            pontosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
            pontosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
            pontosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2); 
            pontosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);
        }

    }
    
}

Lista pontosDentroRetanguloQt(QuadTree quadTree,double x1, double y1,double x2, double y2){
    
    quadtree* qt = (quadtree*) quadTree;

    if(qt == NULL){
        return NULL;
    }
    
    Lista list = criarLista();
    pontosDentroRetanguloQt_aux(qt->raiz, list, x1, y1, x2, y2);

    return list;
}

void pontosDentroCirculoQt_aux(quadNode *qNode,Lista list, double x, double y, double r){
    
    if(qNode == NULL){
        return;
    }

    Info info = getInfoQt(NULL,qNode);
    ponto pnt = retornaInfoCoord(info);

    if(verificaInteriorCirc(x,y,r,info)==0 && qNode->cleared==0){
        ponto novoPonto = montaPonto(retornaPonto_X(pnt),retornaPonto_Y(pnt));
        Info infoPonto = montaInfo("ps","null",novoPonto);
        insertAfterLast(list,infoPonto);

        pontosDentroCirculoQt_aux(qNode->se, list, x, y, r);
        pontosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
        pontosDentroCirculoQt_aux(qNode->sw, list, x, y, r); 
        pontosDentroCirculoQt_aux(qNode->nw, list, x, y, r);
        
    }else{

        if(retornaPonto_Y(pnt) < y-r && retornaPonto_X(pnt) > x+r) pontosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
        else if(retornaPonto_Y(pnt) < y-r && retornaPonto_X(pnt) < x-r) pontosDentroCirculoQt_aux(qNode->nw, list, x, y, r);
        else if(retornaPonto_Y(pnt) > y+r && retornaPonto_X(pnt) < x-r) pontosDentroCirculoQt_aux(qNode->sw, list, x, y, r);
        else if(retornaPonto_Y(pnt) > y+r && retornaPonto_X(pnt) > x+r) pontosDentroCirculoQt_aux(qNode->se, list, x, y, r);

        //checa se o elemento esta acima do circulo (verifica somente ne e nw)
        else if(retornaPonto_Y(pnt) < y-r){
            pontosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
            pontosDentroCirculoQt_aux(qNode->nw, list, x, y, r);
        }

        //checa se o elemento esta abaixo do circulo (verifica somente se e sw)
        else if(retornaPonto_Y(pnt) > y+r){
            pontosDentroCirculoQt_aux(qNode->se, list, x, y, r);
            pontosDentroCirculoQt_aux(qNode->sw, list, x, y, r);
        }

        //checa se o elemento esta do lado esquerdo do circulo (verifica somente sw e nw)
        else if(retornaPonto_X(pnt) < x-r){
            pontosDentroCirculoQt_aux(qNode->sw, list, x, y, r);
            pontosDentroCirculoQt_aux(qNode->nw, list, x, y, r);
        }

        //checa se o elemento esta do lado direito do circulo (verifica somente se e ne)
        else if(retornaPonto_X(pnt) > x+r){
            pontosDentroCirculoQt_aux(qNode->se, list, x, y, r);
            pontosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
        }

        else{
            pontosDentroCirculoQt_aux(qNode->se, list, x, y, r);
            pontosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
            pontosDentroCirculoQt_aux(qNode->sw, list, x, y, r); 
            pontosDentroCirculoQt_aux(qNode->nw, list, x, y, r);
        }
    }

}

Lista pontosDentroCirculoQt(QuadTree quadTree,double x, double y, double r){

    quadtree* qt = (quadtree*) quadTree;

    if(qt == NULL){
        return NULL;
    }

    Lista list = criarLista();
    pontosDentroCirculoQt_aux(qt->raiz, list, x, y, r);

    return list;
}

QtNo insereQt(QuadTree quadTree, ponto p, Info pInfo){

    quadtree *qt = (quadtree*) quadTree;
    
    if(qt->raiz == NULL){
        quadNode *qNode = criaQuadNode(pInfo,p);
        qt->raiz = qNode;
        qt->tamanho++;
        return qNode;
    }

    else{

        quadNode *pai;
        quadNode *temp = qt->raiz;

        int regiao;
        
        while(temp != NULL){
            
            pai = temp;
            
            double nodeAtual_X = retornaPonto_X(temp->coord);
            double nodeAtual_Y = retornaPonto_Y(temp->coord);

            double nodeInsert_X = retornaPonto_X(p);
            double nodeInsert_Y = retornaPonto_Y(p);

            if( (nodeInsert_X < nodeAtual_X && nodeInsert_Y <= nodeAtual_Y) || (nodeInsert_X == nodeAtual_X && nodeInsert_Y == nodeAtual_Y)){ // SE
                temp = temp->se;
                regiao = 1;
            }
            
            else if(nodeInsert_X >= nodeAtual_X && nodeInsert_Y < nodeAtual_Y){ // SW
                temp = temp->sw;
                regiao = 2;
            }
            
            else if(nodeInsert_X <= nodeAtual_X && nodeInsert_Y > nodeAtual_Y){ // NE
                temp = temp->ne;
                regiao = 3;
            }

            else if(nodeInsert_X > nodeAtual_X && nodeInsert_Y >= nodeAtual_Y){ // NW
                temp = temp->nw;
                regiao = 4;
            }
        }

        temp = criaQuadNode(pInfo,p);
        
        if(regiao == 1)
            pai->se = temp;

        else if(regiao == 2)
            pai->sw = temp;

        else if(regiao == 3)
            pai->ne = temp;

        else if(regiao == 4)
            pai->nw = temp;

        qt->tamanho++;

        return temp;
    }
}


int quadTreeToArray(QtNo postos, ponto *array, int tam){
    if(postos == NULL)  return tam;
    quadNode *qNode = (quadNode*) postos;

    if(qNode->cleared == 0){

        ponto p = montaPonto(retornaPonto_X(qNode->coord),retornaPonto_Y(qNode->coord));
        array[tam] = p;
        
        tam = tam-1;
    }

    tam = quadTreeToArray(qNode->se, array, tam);
    tam = quadTreeToArray(qNode->ne, array, tam);
    tam = quadTreeToArray(qNode->sw, array, tam);
    tam = quadTreeToArray(qNode->nw, array, tam);
}


void percorreProfundidadeQt_aux(quadNode *qNode,funcVisita func,ExtraInfo ei){

    if(qNode == NULL) return;

    if(qNode->cleared == 0){
        func(qNode->info,ei);
    }

    percorreProfundidadeQt_aux(qNode->se,func,ei);
    percorreProfundidadeQt_aux(qNode->ne,func,ei);
    percorreProfundidadeQt_aux(qNode->sw,func,ei); 
    percorreProfundidadeQt_aux(qNode->nw,func,ei);
}

void percorreProfundidadeQt(QuadTree quadTree,funcVisita func,ExtraInfo ei){
    quadtree *qt = (quadtree*)quadTree;
    percorreProfundidadeQt_aux(qt->raiz,func,ei);
}

void percorreLarguraQt(QuadTree quadTree, funcVisita f , ExtraInfo ei){  

    quadtree *qt = (quadtree*) quadTree;
    quadNode *qNode = getNoQt_root(qt);

    Lista fila = criarLista();

    insertAfterLast(fila, qNode);
    nodulo node = getFirst(fila);

    while(node){

        node = getFirst(fila);

        if(node == NULL){
            break;
        }

        quadNode* qNodeAtual = (quadNode*) getInfo(node); // quadNode

        f(qNodeAtual->info,ei); // funcao visita

        if(qNodeAtual->ne){
            insertAfterLast(fila,qNodeAtual->ne);
        }

        if(qNodeAtual->nw){
            insertAfterLast(fila,qNodeAtual->nw);
        }

        if(qNodeAtual->se){
            insertAfterLast(fila,qNodeAtual->se);
        }

        if(qNodeAtual->sw){
            insertAfterLast(fila,qNodeAtual->sw);
        }

        node = removeFirst(fila);

    }

}

void desalocaQt_aux2(quadNode *qNode, void(*freeElements)(void*)){

    if(qNode == NULL) return;

    if(freeElements!=NULL){
        freeElements(qNode->info);
    }
    
    desalocaQt_aux2(qNode->se, freeElements);
    desalocaQt_aux2(qNode->ne, freeElements);
    desalocaQt_aux2(qNode->sw, freeElements);
    desalocaQt_aux2(qNode->nw, freeElements); 

    free(qNode);
}

void desalocaQt2(QuadTree quadTree, void(*freeElements)(void*)){
    quadtree *qt = (quadtree*) quadTree;
    desalocaQt_aux2(qt->raiz, freeElements);
    free(qt);
}

void desalocaQt_aux(quadNode *qNode){

    if(qNode == NULL) return;

    removeInfo(qNode->info);
    
    desalocaQt_aux(qNode->se);
    desalocaQt_aux(qNode->ne);
    desalocaQt_aux(qNode->sw);
    desalocaQt_aux(qNode->nw); 

    free(qNode);
}

void desalocaQt(QuadTree quadTree){
    quadtree *qt = (quadtree*) quadTree;

    desalocaQt_aux(qt->raiz);
    free(qt);
}

QtInfo getInfoQt(QuadTree quadTree, QtNo pNo){

    if(pNo == NULL){
        return NULL;
    }

    quadNode *qNode = (quadNode*) pNo;

    return qNode->info;
}

quadNode *getNoQt_byId_aux(quadNode *qNode, char *Id, char*(*getId)(void*)){

    if(qNode == NULL) return NULL;

    Modulo objeto = getModulo(qNode->info);

    quadNode *qtNo = NULL;

    if(strcmp(getId(objeto), Id)==0 && qNode->cleared==0){
        qtNo = qNode;
    }

    if(qtNo == NULL){
        qtNo = getNoQt_byId_aux(qNode->se,Id,getId);
    }

    if(qtNo == NULL){
        qtNo = getNoQt_byId_aux(qNode->ne,Id,getId);
    }

    if(qtNo == NULL){
        qtNo = getNoQt_byId_aux(qNode->sw,Id,getId);
    }

    if(qtNo == NULL){
        qtNo = getNoQt_byId_aux(qNode->nw,Id,getId);
    }

    return qtNo;
}

QtNo getNoQt_byId(QuadTree quadTree, char *Id){

    quadtree *qt = (quadtree*) quadTree;
    quadNode *qNode = getNoQt_byId_aux(qt->raiz,Id,qt->getId);
    
    return qNode;
}

QtNo getNoQt_root(QuadTree quadTree){

    if(quadTree == NULL) return NULL;
    quadtree *qt = (quadtree*) quadTree;

    return qt->raiz;
}

Info removeQt(QuadTree quadTree, QtNo pNo){

    quadNode *qNode = (quadNode*)pNo;
    quadtree *qt = (quadtree*)quadTree;
    int deletado = 0;

    Info info = qNode->info;

    if(qNode->cleared == 0){
        qNode->cleared = 1;
        deletado = 1;
    }
    
    return info;
}

QtNo findNodeQt(QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree torresCel, QuadTree semaforos, QuadTree quadras, char *id){

    QtNo node = getNoQt_byId(circulos, id);
        
    if(node == NULL){
        node = getNoQt_byId(retangulos, id);
    }

    if(node == NULL){
        node = getNoQt_byId(textos, id);
    }      

    if(node == NULL){
        node = getNoQt_byId(hidrantes, id);
    }    

    if(node == NULL){
        node = getNoQt_byId(torresCel, id);
    }    

    if(node == NULL){
        node = getNoQt_byId(semaforos, id);
    }   

    if(node == NULL){
        node = getNoQt_byId(quadras, id);
    }     

    return node;

}

int getQt_ObjAmount(QuadTree quadTree){
    quadtree *qt = (quadtree*)quadTree;
    return qt->tamanho;
}

void nosDentroRetanguloQt_aux(quadNode *qNode, Lista list, double x1, double y1, double x2, double y2){

    if(qNode == NULL){
        return;
    }

    if(qNode->cleared == 0 && verificaInteriorRet(x1, y1, x2, y2, qNode->info)==0){

        insertAfterLast(list, qNode->info);

        nosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
        nosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
        nosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2); 
        nosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);

    }else{

        Info info = getInfoQt(NULL,qNode);
        ponto pnt = retornaInfoCoord(info);

        //checa se o elemento esta nos cantos ao redor do retangulo
        if(retornaPonto_Y(pnt) < y1 && retornaPonto_X(pnt) > x2) nosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
        else if(retornaPonto_Y(pnt) < y1 && retornaPonto_X(pnt) < x1) nosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);
        else if(retornaPonto_Y(pnt) > y2 && retornaPonto_X(pnt) < x1) nosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2);
        else if(retornaPonto_Y(pnt) > y2 && retornaPonto_X(pnt) > x2) nosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
        
        //checa se o elemento esta acima do retangulo (verifica somente ne e nw)
        else if(retornaPonto_Y(pnt) < y1){
            nosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
            nosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);
        }

        //checa se o elemento esta abaixo do retangulo (verifica somente se e sw)
        else if(retornaPonto_Y(pnt) > y2){
            nosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
            nosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2);
        }

        //checa se o elemento esta do lado esquerdo do retangulo (verifica somente sw e nw)
        else if(retornaPonto_X(pnt) < x1){
            nosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2);
            nosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);
        }

        //checa se o elemento esta do lado direito do retangulo (verifica somente se e ne)
        else if(retornaPonto_X(pnt) > x2){
            nosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
            nosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
        }

        else{
            nosDentroRetanguloQt_aux(qNode->se, list, x1, y1, x2, y2);
            nosDentroRetanguloQt_aux(qNode->ne, list, x1, y1, x2, y2);
            nosDentroRetanguloQt_aux(qNode->sw, list, x1, y1, x2, y2); 
            nosDentroRetanguloQt_aux(qNode->nw, list, x1, y1, x2, y2);
        }

    }

}

Lista nosDentroRetanguloQt(QuadTree quadTree,double x1, double y1,double x2, double y2){
    
    quadtree* qt = (quadtree*) quadTree;

    if(qt == NULL){
        return NULL;
    }
    
    Lista list = criarLista();
    nosDentroRetanguloQt_aux(qt->raiz, list, x1, y1, x2, y2);

    return list;
}

void nosDentroCirculoQt_aux(quadNode *qNode, Lista list, double x, double y, double r){
    
    if(qNode == NULL){
        return;
    }
    
    if(qNode->cleared == 0 && verificaInteriorCirc(x,y,r, qNode->info)==0){
        
        insertAfterLast(list,qNode->info);

        nosDentroCirculoQt_aux(qNode->se, list, x, y, r);
        nosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
        nosDentroCirculoQt_aux(qNode->sw, list, x, y, r); 
        nosDentroCirculoQt_aux(qNode->nw, list, x, y, r);

    }else{
        Info info = getInfoQt(NULL,qNode);
        ponto pnt = retornaInfoCoord(info);

        if(retornaPonto_Y(pnt) < y-r && retornaPonto_X(pnt) > x+r) nosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
        else if(retornaPonto_Y(pnt) < y-r && retornaPonto_X(pnt) < x-r) nosDentroCirculoQt_aux(qNode->nw, list, x, y, r);
        else if(retornaPonto_Y(pnt) > y+r && retornaPonto_X(pnt) < x-r) nosDentroCirculoQt_aux(qNode->sw, list, x, y, r);
        else if(retornaPonto_Y(pnt) > y+r && retornaPonto_X(pnt) > x+r) nosDentroCirculoQt_aux(qNode->se, list, x, y, r);

        //checa se o elemento esta acima do circulo (verifica somente ne e nw)
        else if(retornaPonto_Y(pnt) < y-r){
            nosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
            nosDentroCirculoQt_aux(qNode->nw, list, x, y, r);
        }

        //checa se o elemento esta abaixo do circulo (verifica somente se e sw)
        else if(retornaPonto_Y(pnt) > y+r){
            nosDentroCirculoQt_aux(qNode->se, list, x, y, r);
            nosDentroCirculoQt_aux(qNode->sw, list, x, y, r);
        }

        //checa se o elemento esta do lado esquerdo do circulo (verifica somente sw e nw)
        else if(retornaPonto_X(pnt) < x-r){
            nosDentroCirculoQt_aux(qNode->sw, list, x, y, r);
            nosDentroCirculoQt_aux(qNode->nw, list, x, y, r);
        }

        //checa se o elemento esta do lado direito do circulo (verifica somente se e ne)
        else if(retornaPonto_X(pnt) > x+r){
            nosDentroCirculoQt_aux(qNode->se, list, x, y, r);
            nosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
        }

        else{
            nosDentroCirculoQt_aux(qNode->se, list, x, y, r);
            nosDentroCirculoQt_aux(qNode->ne, list, x, y, r);
            nosDentroCirculoQt_aux(qNode->sw, list, x, y, r); 
            nosDentroCirculoQt_aux(qNode->nw, list, x, y, r);
        }
    }

}

Lista nosDentroCirculoQt(QuadTree quadTree, double x, double y, double r){

    quadtree* qt = (quadtree*) quadTree;

    if(qt == NULL){
        return NULL;
    }

    Lista list = criarLista();
    nosDentroCirculoQt_aux(qt->raiz, list, x, y, r);

    return list;
}

int isCleared(QtNo qNode){
    quadNode* qt = (quadNode*) qNode;

    return qt->cleared;
}

QtNo getNE(QtNo qNode){
    quadNode* qt = (quadNode*) qNode;

    return qt->ne;
}

QtNo getNW(QtNo qNode){
    quadNode* qt = (quadNode*) qNode;

    return qt->nw;
}

QtNo getSE(QtNo qNode){
    quadNode* qt = (quadNode*) qNode;

    return qt->se;
}

QtNo getSW(QtNo qNode){
    quadNode* qt = (quadNode*) qNode;

    return qt->sw;
}

void ordenaInsercaoQt(QuadTree quadTree, Lista list){

    Lista stack = criarLista();
    
    while(listSize(list) != 0){
        Info *array = (Info*) malloc(sizeof(Info)*listSize(list));
        
        int i=0;
        nodulo node = getFirst(list);

        while(node!=NULL){
            array[i] = getInfo(node);
            i++;
            node = getNext(node);
        }

        Lista envoltoria = envoltoriaConvexa(array,listSize(list));
        free(array);
        if(envoltoria != NULL){

            while(listSize(envoltoria)!=0){
                Info info = removeLast(envoltoria);
                insertAfterLast(stack,info);

                nodulo nodeList = findNode_byInfo(list,info);
                removeNode(nodeList,list);
            }

            limparLista_aux(envoltoria);
        }else{
            nodulo nodeList = getLast(list);
            while(nodeList != NULL){
                Info info = removeLast(list);
                insertAfterLast(stack,info);
                
                nodeList = getLast(list);
            }
        }
    }

    nodulo nodeStack = getLast(stack);

    while(nodeStack != NULL){
        Info info = removeLast(stack);
        ponto p = retornaInfoCoord(info);

        insereQt(quadTree,p,info);

        nodeStack = getLast(stack);
    }
    
    limparLista_aux(stack);
}

void recriaQt_aux(quadtree *qt, quadNode *raiz){

    if(raiz == NULL){
        return;
    } 

    if(raiz->cleared == 0){
        insereQt(qt,raiz->coord,raiz->info);
    }else{
        removeInfo(raiz->info);
    }

    recriaQt_aux(qt,raiz->ne);
    recriaQt_aux(qt,raiz->nw);
    recriaQt_aux(qt,raiz->se);
    recriaQt_aux(qt,raiz->sw);

    free(raiz);
}

void recriaQt(QuadTree quadTree){
    
    quadtree *qt = (quadtree*)quadTree;
    quadNode *raiz = qt->raiz;

    qt->tamanho = 0;
    qt->raiz = NULL;

    recriaQt_aux(qt,raiz);
}
