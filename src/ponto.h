#ifndef __ponto_h
#define __ponto_h

typedef void *ponto; 

/*
*   cria um objeto do tipo ponto
*   necessita das informações do ponto
*   retorna um objeto tipo ponto
*/
ponto montaPonto(double x, double y);

/*
*   altera a coordenada x de um objeto tipo ponto
*   necessita do ponteiro para objeto tipo ponto e do novo valor 
*   nao retorna nada
*/
void alteraPonto_X(ponto p, double n);

/*
*   altera a coordenada y de um objeto tipo ponto
*   necessita do ponteiro para objeto tipo ponto e do novo valor 
*   nao retorna nada
*/
void alteraPonto_Y(ponto p, double n);
/*
*   cria um vetor de pontos
*   necessita do numero de pontos
*   retorna um vetor de pontos
*/
ponto *criaArrayPontos(int tamanho);

/*
*   necessita de um objeto do tipo ponto
*   retorna x do ponto recebido
*/
double retornaPonto_X(ponto c);

/*
*   necessita de um objeto do tipo ponto
*   retorna y do ponto recebido
*/
double retornaPonto_Y(ponto c);

/*
*   necessita do ponteiro para objeto tipo ponto e do novo valor 
*   retorna a funcao de Id do ponto (none)
*/
char *retornaChaveExtra();


/*  deleta o objeto de tipo ponto
*   necessita de um objeto do tipo ponto 
*   não retorna nada
*/
void removePonto(ponto c);

#endif