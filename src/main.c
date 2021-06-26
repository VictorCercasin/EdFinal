#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "lista.h"
#include "svg.h"
#include "learq.h"
#include "leqry.h"
#include "pathment.h"
#include "txt.h"
#include "quadtree.h"
#include "hashTable.h"
#include "ponto.h"

void main(int argc, char *argv[]){

    diretorio dir = setPaths(argc,argv);

    FILE* fileQRY; 
    FILE* svgGeo;
    FILE* svgQry;

    char line[256];
    char mat[50][50];
    int i;

    QuadTree circulos = criaQt(retornaCirc_Id);
    QuadTree retangulos = criaQt(retornaRet_Id);
    QuadTree textos = criaQt(retornaTexto_Id);
    QuadTree quadras = criaQt(retornaQuadra_Cep);
    QuadTree hidrantes = criaQt(retornaCirc_Id);
    QuadTree semaforos = criaQt(retornaCirc_Id);
    QuadTree torresCelular = criaQt(retornaCirc_Id);
    QuadTree postos = criaQt(retornaChaveExtra);
    QuadTree regioes = criaQt(retornaChaveExtra);

    Lista casas = criarLista(); 
    Lista poligonos = criarLista(); 
    Lista listQRY = criarLista();

    Lista moradores = criarLista();
    Lista estabComerc = criarLista();

    HashTable cepXquadra = criaHt(80);
    HashTable codtXdesc = criaHt(80);
    HashTable cpfXcep = criaHt(80);
    HashTable cpfXpessoa = criaHt(80);

    Grafo grafo = NULL;
    Grafo arvoreGeradoraMin = NULL;
    char *pathSvgAuxiliar = "vazio";

    ponto *registradores = criaArrayPontos(11);
    memset(registradores, 0, sizeof(ponto) * 11);

    lerArqGeo(path_pathGeo(dir), cepXquadra ,circulos, retangulos, textos, hidrantes, quadras, torresCelular, semaforos, postos, regioes); 
    svgGeo = fopen(path_pathSvg_geo(dir), "w");
    transfSVG(svgGeo, listQRY, poligonos, circulos, retangulos, textos, hidrantes, quadras, torresCelular, semaforos, postos, casas);
    fclose(svgGeo);

    if(path_Pm(dir) != NULL){ 
        lerArqPm(path_Pm(dir),moradores,cpfXpessoa,cepXquadra,cpfXcep);
    }

    if(path_Ec(dir) != NULL){
        lerArqEc(path_Ec(dir),codtXdesc, cpfXpessoa, estabComerc, cepXquadra);
    }

    if(path_Via(dir) != NULL){
        grafo = lerArqVia(path_Via(dir));
    }

    if(path_nomeArqQry(dir) !=NULL){
                    
        fileQRY = fopen(path_pathQry(dir),"r");

        criarTxt(path_pathTxt(dir));

        while(fgets(line,sizeof(line),fileQRY)){
            i = funcLer(line,mat);
            menuQRY(path_pathTxt(dir), grafo, &arvoreGeradoraMin, registradores , moradores,listQRY, circulos, retangulos, textos, hidrantes, torresCelular, semaforos, quadras, regioes,casas, postos, poligonos, mat,i, cepXquadra, cpfXpessoa, codtXdesc, cpfXcep, estabComerc, &pathSvgAuxiliar);
        }
        
        if(strcmp(pathSvgAuxiliar,"vazio")!=0){
            FILE *svgSufixo =  fopen(pathSvgAuxiliar, "a+");
            fprintf(svgSufixo, "\n</svg>");
            fclose(svgSufixo);
            free(pathSvgAuxiliar);
        }

        svgQry = fopen(path_pathSvg_qry(dir),"w");

        transfSVG(svgQry, listQRY, poligonos, circulos, retangulos, textos, hidrantes, quadras, torresCelular, semaforos, postos, casas);

        fclose(svgQry);
        fclose(fileQRY);
    }
    
    for(int i=0;i<11;i++){
        if(registradores[i]!=NULL){
            removePonto(registradores[i]);
        }
    }
    
    free(registradores);

    desalocaHT_del(cpfXcep);
    desalocaHT_del(codtXdesc);
    desalocaHT_del(cpfXpessoa);
    desalocaHT(cepXquadra);
                                               
    desalocaQt(circulos);
    desalocaQt(retangulos);
    desalocaQt(textos);
    desalocaQt(hidrantes);
    desalocaQt(semaforos);
    desalocaQt(quadras);
    desalocaQt(torresCelular);
    desalocaQt(postos);
    desalocaQt(regioes);

    limparLista(poligonos);
    limparLista(casas);
    limparLista(listQRY);
    limparLista(moradores);
    limparLista(estabComerc);

    removeGrafo_Aux(arvoreGeradoraMin);
    removeGrafo(grafo);

    free_paths(dir);
}