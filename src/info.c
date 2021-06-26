#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "info.h"
#include "morador.h"
#include "pessoa.h"
#include "estabComerc.h"
#include "grafo.h"

typedef struct inf
{
    char pos[100];
    char tipo[100];
    Modulo obj;
} info;

Info montaInfo(char *tipo, char *pos, Modulo elemento){
    
    info *informacoes;
    informacoes = (info *) calloc (1, sizeof(info));
    strcpy(informacoes->pos,pos);
    strcpy(informacoes->tipo,tipo); 

    informacoes->obj = elemento;

    return informacoes;
}

char *retornaPos(Info inf){
    info *informacoes = (info *) inf;
    return informacoes-> pos;
}

char *retornaTipo(Info inf){
    info *informacoes = (info *) inf;
    return informacoes-> tipo;
}

Modulo getModulo(Info inf){
    info *informacoes = (info*) inf;
    return informacoes->obj;
}

ponto retornaInfoCoord(Info info){

    if(strcmp(retornaTipo(info),"c") == 0 || strcmp(retornaTipo(info),"rb") ==0 || strcmp(retornaTipo(info),"s")==0 || strcmp(retornaTipo(info), "h" )==0 || strcmp(retornaTipo(info),"circulo") == 0){
        return retornaCircCoord(getModulo(info));
    }

    else if(strcmp("r",retornaTipo(info))==0){
        return retornaRetCoord(getModulo(info));
    }

    else if(strcmp(retornaTipo(info),"q")==0){
        return retornaQuadraCoord(getModulo(info));
    }

    else if(strcmp("t",retornaTipo(info))==0){
        return retornaTextoCoord(getModulo(info));
    }

    else if(strcmp("ps",retornaTipo(info))==0){
        return getModulo(info);
    }
    
    else if(strcmp("cv",retornaTipo(info))==0){
        return retornaCasaCoord(getModulo(info));
    }
    
    else if(strcmp("dd",retornaTipo(info))==0){
        return retornaRegiaoCoord(getModulo(info));
    }

    else if(strcmp("vertice",retornaTipo(info))==0){
        return retornaVerticeCoord(getModulo(info));
    }

}

void removeObjeto(Info info){

    if(strcmp(retornaTipo(info),"c") == 0 || strcmp(retornaTipo(info),"rb") ==0 || strcmp(retornaTipo(info),"s")==0 || strcmp(retornaTipo(info), "h")==0 || strcmp(retornaTipo(info), "circCalac")==0 || strcmp(retornaTipo(info), "circulo")==0){
        removeCirculo(getModulo(info));
        
    }


    else if(strcmp("r",retornaTipo(info))==0 || strcmp(retornaTipo(info),"rA")==0 || strcmp(retornaTipo(info),"l")==0 ||  strcmp(retornaTipo(info),"lt")==0 || strcmp(retornaTipo(info),"e")==0 || strcmp(retornaTipo(info),"d")==0){
        removeRetangulo(getModulo(info));
    }

    else if(strcmp(retornaTipo(info),"q")==0){
        removeQuadra(getModulo(info));
    }

    else if(strcmp("t",retornaTipo(info))==0){
        removeTexto(getModulo(info));
    }

    else if(strcmp("ps",retornaTipo(info))==0 || strcmp("pontoEc",retornaTipo(info))==0 || strcmp("pontoCor",retornaTipo(info))==0){
        removePonto(getModulo(info));
    }
    
    else if(strcmp("cv",retornaTipo(info))==0){
        removeCasa(getModulo(info));
    }
    
    else if(strcmp("poly",retornaTipo(info))==0){
        removePoligono(getModulo(info));
    }

    else if(strcmp("dd",retornaTipo(info))==0){
        removeRegiao(getModulo(info));
    }

    else if(strcmp("pessoa",retornaTipo(info))==0){
        removePessoa(getModulo(info));
    }

    else if(strcmp("morador",retornaTipo(info))==0){
        removeMorador(getModulo(info));
    }

    else if(strcmp("str",retornaTipo(info))==0){
        removeString(getModulo(info));
    }

    else if(strcmp("ec",retornaTipo(info))==0){
        removeEc(getModulo(info));
    }

    else if(strcmp("vertice",retornaTipo(info))==0){
        return;
    }

    else{
        free(getModulo(info));
    }

}

void removeInfo(Info inf){
    info *informacoes = (info *) inf;

    removeObjeto(inf);
    free(informacoes);
}

