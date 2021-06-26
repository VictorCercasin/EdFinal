#ifndef __texto_h
#define __texto_h

#include "ponto.h"

typedef void *texto; 

/*
*   cria um objeto do tipo texto    
*   necessita das informações do texto
*   retorna um objeto do tipo texto
*/
texto montaTexto(char *id, double x, double y, char *corb, char *corp, char *conteudo, int TotalLen);

/*
*   altera a cor de preenchimento do texto recebido
*   nao retorna nada
*/
void alteraTexto_Corp(texto t, char *corp);

/*
*   altera a cor de borda do texto recebido 
*   nao retorna nada
*/
void alteraTexto_Corb(texto t, char *corb);

/*
*   pega o x do texto
*   necessita do objeto de tipo texto
*   retorna x do objeto de tipo texto
*/
double retornaTexto_X(texto t);


/*
*   pega o y do texto
*   necessita do objeto de tipo texto
*   retorna y do objeto de tipo texto
*/
double retornaTexto_Y(texto t);


/*
*   pega a id do texto
*   necessita do objeto de tipo texto
*   retorna a id do objeto de tipo texto
*/
char *retornaTexto_Id(texto t);

/*
*   pega a cor de preenchimento do texto
*   necessita do objeto de tipo texto
*   retorna a cor de preenchimento do objeto de tipo texto
*/
char *retornaTexto_Corp(texto t);


/*
*   pega a cor de borda do texto
*   necessita do objeto de tipo texto
*   retorna a cor de borda do objeto de tipo texto
*/
char *retornaTexto_Corb(texto t);

/*
*   pega o conteudo do texto
*   necessita do arquivo SVG e de um objeto do tipo círculo
*   retorna o conteudo do obejto de tipo texto
*/
char *retornaConteudo(texto t);

/*
*   necessita de um objeto do tipo texto
*   retorna o objeto do tipo ponto (coordenadas (x,y)) associado ao objeto de tipo texto
*/
ponto retornaTextoCoord(texto t);

/*
*   deleta o objeto de tipo texto
*   necessita do objeto de tipo texto
*   não retorna nada
*/
void removeTexto(texto t);

#endif