#ifndef __regiao_h
#define __regiao_h

#include "ponto.h"

typedef void *regiao; 


/*
*   cria um objeto do tipo regiao
*   necessita das informações da regiao
*   retorna um objeto do tipo regiao
*/
regiao montaRegiao(double x,double y, double w, double h, double d);

/*
*   pega o x da regiao 
*   necessita de um objeto do tipo regiao
*   retorna o x da regiao recebida
*/
double retornaReg_X(regiao r);

/*
*   pega o y da regiao 
*   necessita de um objeto do tipo regiao
*   retorna o y da regiao recebida
*/
double retornaReg_Y(regiao r);

/*
*   pega a largura da regiao 
*   necessita de um objeto do tipo regiao
*   retorna a largura da regiao recebida
*/
double retornaReg_W(regiao r);

/*
*   pega a altura da regiao 
*   necessita de um objeto do tipo regiao
*   retorna a altura da regiao recebida
*/
double retornaReg_H(regiao r);

/*
*   pega a densidade demográfica da regiao 
*   necessita de um objeto do tipo regiao
*   retorna a densidade demográfica da regiao recebida
*/
double retornaReg_D(regiao r);


/*
*   pega a o objeto do tipo ponto associado ao objeto tipo regiao
*   necessita de um objeto do tipo regiao
*   retorna a o objeto tipo ponto (coordenadas(x,y)) da regiao recebida
*/
ponto retornaRegiaoCoord(regiao r);

/*
*   deleta o objeto de tipo regiao
*   necessita de um objeto do tipo regiao
*   não retorna nada
*/
void removeRegiao(regiao r);

#endif