#ifndef __retangulo_h
#define __retangulo_h

#include "ponto.h"

typedef void *retangulo; 


/*
*   cria um objeto do tipo retangulo
*   necessita das informações do retangulo
*   retorna um objeto do tipo retangulo
*/
retangulo montaRetangulo(char *id,char *sw, double w,double h, double x, double y, char *corb, char *corp);


/*
*   pega o x do retangulo 
*   necessita de um objeto do tipo retangulo
*   retorna o x do retangulo recebido
*/
double retornaRet_X(retangulo r);


/*
*   pega o y do retangulo 
*   necessita de um objeto do tipo retangulo
*   retorna o y do retangulo recebido
*/
double retornaRet_Y(retangulo r);


/*
*   pega a largura do retangulo 
*   necessita de um objeto do tipo retangulo
*   retorna a largura do retangulo recebido
*/
double retornaRet_W(retangulo r);

/*
*   pega a altura do retangulo 
*   necessita de um objeto do tipo retangulo
*   retorna a altura do retangulo recebido
*/
double retornaRet_H(retangulo r);

/*
*   pega a id do retangulo 
*   necessita de um objeto do tipo retangulo
*   retorna a id do retangulo recebido
*/
char *retornaRet_Id(retangulo r);

/*
*   pega a cor de preenchimento do retangulo 
*   necessita de um objeto do tipo retangulo
*   retorna a cor de preenchimento do retangulo recebido
*/
char *retornaRet_Corp(retangulo r);

/*
*   pega a cor de borda do retangulo 
*   necessita de um objeto do tipo retangulo
*   retorna a cor de borda do retangulo recebido
*/
char *retornaRet_Corb(retangulo r);

/*
*   deleta o objeto de tipo  retangulo
*   necessita de um objeto do tipo retangulo
*   não retorna nada
*/
void removeRetangulo(retangulo r);

/*
*   necessita de um objeto do tipo retangulo
*   retorna o ponteiro para o objeto tipo ponto
*/
ponto retornaRetCoord(retangulo r);

/*
*   altera a cor de borda do retangulo
*   necessita de um objeto do tipo retangulo e da cor de borda
*   não retorna nada
*/
void alteraRet_Corb(retangulo r, char *corb);

/*
*   altera a cor de preenchimento do retangulo
*   necessita de um objeto do tipo retangulo e da cor de preenchimento
*   não retorna nada
*/
void alteraRet_Corp(retangulo r, char *corp);

/*
*   pega a largura da borda do retangulo 
*   necessita de um objeto do tipo retangulo
*   retorna a largura da borda do retangulo recebido
*/
char *retornaRet_SW(retangulo r);

#endif