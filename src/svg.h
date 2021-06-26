#ifndef SVG_H
#define SVG_H

#include "lista.h"
#include "quadtree.h"
#include "estabComerc.h"
#include "ponto.h"
#include "quadra.h"
#include "grafo.h"

/*
*   menu que direciona para diferentes funções imprimirem conteúdo de uma lista em um arquivo SVG
*   necessita do arquivo svg e de uma lista
*   não retorna nada
*/
void escreveSVG(FILE *fileSVG, Lista lista);

/*
*   direciona cada lista para a função escreveSVG
*   necessita de todas as listas
*   não retorna nada
*/
void transfListasSVG(FILE *fileSVG,Lista listQRY, Lista poligonos);

/*
*   verifica qual e o tipo de elemento a ser colocado no arquivo svg e direciona a funcao de imprimir correta
*   necessita da informacao Info que contem a figura/objeto a ser impresso no svg de path 'file'
*   não retorna nada
*/
void selecionaTipoSVG(Info info, void *file);

/*
*   Cria o circulo do comando catac
*   necessita das informacoes do circulo e da lista a qual ele sera inserido
*   não retorna nada
*/
void carregaCircCalac(Lista list, double x, double y, double r, char *corp, char *corb);

/*
*   Imprime no svg o circulo do comando catac
*   necessita da path e do objeto contendo as informacoes do circulo
*   não retorna nada
*/
void insereCircCalac(FILE *path, Modulo c);

/*
*   Imprime no svg um ponto generico
*   necessita da path e do objeto (Info) que contem o elemento (Modulo) contendo as informacoes a serem impressas
*   não retorna nada
*/
void inserePontoGen(FILE *fileSVG, Info info);

/*
*   Transfere todas as listas e quadtrees para serem impressas no svg
*   necessita da path do SVG, das listas e quadtrees a serem impressas
*   não retorna nada
*/
void transfSVG(FILE *fileSVG, Lista listQRY, Lista poligonos, QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree quadras, QuadTree radioTorres, QuadTree semaforos, QuadTree pontos, Lista casas);


void transfSVGgeo(FILE *fileSVG, QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree quadras, QuadTree radioTorres, QuadTree semaforos, QuadTree pontos);

/*
*   insere um circulo no arquivo svg
*   necessita do arquivo SVG e de um objeto do tipo círculo
*   não retorna nada
*/
void insereCirculoC(FILE *path,Modulo circ);
void insereCirculo(FILE *path, Modulo circ);

/*
*   cria um ponto contendo as coordenadas (x,y)
*   necessita da lista a qual ele sera inserido e de sua cor de preenchimento
*   não retorna nada
*/
void carregaPonto(Lista lista, double x, double y, char *corp);

/*
*   insere um  retangulo no arquivo SVG
*   necessita do arquivo SVG e de um objeto do tipo retangulo
*   não retorna nada
*/
void insereRetangulo(FILE *path, Modulo ret);

/*
*   cria uma linha entre dois pontos
*   necessita das informacoes da linha e de sua cor
*   não retorna nada
*/
void carregaLinha(Lista lista, double x1, double y1, double x2, double y2, char *cor);

/*
*   insere texto no arquivo svg
*   necessita do arquivo SVG e de um objeto do tipo texto
*   não retorna nada
*/
void insereTexto(FILE *path, Modulo txt);

/*
*   insere um ret tracejado no arquivo svg
*   necessita do arquivo SVG e de um objeto do tipo retangulo
*   não retorna nada
*/
void insereRetTracado(FILE *path, Modulo retTrac);

/*
*   cria um objeto do tipo retangulo
*   necessita da lista qry e das informações do retangulo
*   não retorna nada
*/
void carregaRetTracado(Lista lista, double x, double y, double h, double w);

/*
*   insere um um retangulo vazio no arquivo SVG
*   necessita do arquivo SVG e  um objeto do tipo retangulo
*   não retorna nada
*/
void insereRetLine(FILE *path, Modulo retLine);

/*
*   insere uma linha tracejada no arquivo SVG
*   necessita do arquivo SVG e de um objeto do tipo retangulo
*   não retorna nada
*/
void insereLinhaTracejada(FILE *path, Modulo line);

/*
*   cria um objeto do tipo retangulo
*   necessita da lista qry e das informações do retangulo 
*   não retorna nada
*/
void carregaRetLine(Lista lista,double x,double y, double h, double w);

/*
*   insere um ponto no arquivo SVG
*   necessita da lista de figuras e das informações do ponto
*   nao retorna nada
*/
void inserePonto(Lista lista, nodulo node, double x, double y, char *cor);

/*
*   insere uma linha no arquivo SVG
*   necessita do arquivo SVG e de um objeto do tipo retangulo
*   não retorna nada
*/
void insereLinha(FILE *path,Modulo line);

/*
*   insere uma quadra no arquivo SVG
*   necessita do arquivo SVG e de um objeto do tipo retangulo
*   não retorna nada
*/
void insereQuadra(FILE *path, Modulo quad);

/*
*   insere um hidrante no arquivo SVG
*   necessita do arquivo SVG e de um objeto do tipo circulo
*   não retorna nada
*/
void insereHidrante(FILE *path,Modulo hid);

/*
*   insere um semaforo no arquivo SVG
*   necessita do arquivo SVG e de um objeto do tipo circulo
*   não retorna nada
*/
void insereSemaforo(FILE *path,Modulo semaf);

/*
*   insere uma torre de celular no arquivo SVG
*   necessita do arquivo SVG e de um objeto do tipo circulo
*   não retorna nada
*/
void insereTorreCel(FILE *path,Modulo torreCel);

/*
*   insere um retangulo com borda arredondada no arquivo SVG 
*   necessita do arquivo SVG e de um objeto do tipo retangulo
*   não retorna nada
*/
void insereRetArredondado(FILE *path,Modulo retArred);

/*
*   insere um estabelecimento comercial no arquivo SVG de caminho 'path'
*   necessita do arquivo SVG e de um objeto do tipo estabComercial
*   não retorna nada
*/
void insereEstab(FILE *path, Modulo ec);

/*
*   insere um posto
*   necessita do arquivo SVG e de um objeto do tipo posto
*   não retorna nada
*/
void inserePosto(FILE *path, Modulo p);

/*
*   insere uma casa
*   necessita do arquivo SVG e de um objeto do tipo casa
*   não retorna nada
*/
void insereCasa(FILE *path, Modulo c);

/*
*   insere um poligono
*   necessita do arquivo SVG e de um objeto do tipo poligono
*   não retorna nada
*/
void inserePoligono(FILE *path, Modulo poly);

/*
*   altera a sombra da quadra conforme a densidade populacional de sua regiao
*   necessita de uma lista de quadras e a lista de regioes auxiliares a suas quadtrees
*   não retorna nada
*/
void carregarSombraQuadras(Lista quadras, Lista regioes);

/*
*   imprime o gravo no arquivo svg de path 'pathSvg' com a cor recebida
*   necessita de um grafo, da path do Svg e da cor das linhas a serem feitas entre os vertices
*   não retorna nada
*/
void imprimirGrafo(Grafo grafo, char *pathSvg, char *cor);

/*
*   imprime a quadtree no arquivo SVG 
*   necessita de uma quadtree e o caminho do arquivo 'pathSvg'
*   não retorna nada
*/
void imprimirQuadtree(QuadTree quadTree, char *pathSvg);


/*
*   imprime o caminho no arquivo SVG com a animacao
*   necessita do grafo, do trajeto a ser percorrido, da path do arquivo, da cor do trajeto e do tipo de trajeto(dist/velocidade)
*   nao retorna dada
*/
void imprimePathAnimacaoSvg(char *path, Lista trajeto, Grafo grafo, int tipoPeso, char *cor);

#endif