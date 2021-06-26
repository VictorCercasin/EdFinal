#include "ponto.h"

typedef void *Quadra;

/*
*   cria um objeto tipo Quadra
*   necessita das informacoes da quadra
*   retorna um ponteiro para objeto do tipo Quadra
*/
Quadra montaQuadra(char *id,char *sw ,double w,double h, double x, double y, char *corb, char *corp);

/*
*   pega a coordenada x da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna a coordenada x do objeto tipo Quadra
*/
double retornaQuadra_X(Quadra q);

/*
*   pega a coordenada y da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna a coordenada y do objeto tipo Quadra
*/
double retornaQuadra_Y(Quadra q);

/*
*   pega a largura w da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna a largura do objeto tipo Quadra
*/
double retornaQuadra_W(Quadra q);

/*
*   pega a altura h da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna a altura h do objeto tipo Quadra
*/
double retornaQuadra_H(Quadra q);

/*
*   pega o Cep da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna o cep do objeto tipo Quadra
*/
char *retornaQuadra_Cep(Quadra q);

/*
*   pega a largura da borda da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna a largura da borda do objeto tipo Quadra
*/
char *retornaQuadra_SW(Quadra q);

/*
*   pega a cor de preenchimento da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna a cor de preenchimento do objeto tipo Quadra
*/
char *retornaQuadra_Corp(Quadra q);

/*
*   pega a cor da borda da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna a cor da borda do objeto tipo Quadra
*/
char *retornaQuadra_Corb(Quadra q);

/*
*   pega a cor da sombra da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna a cor da sombra do objeto tipo Quadra
*/
char *retornaQuadra_CorSombra(Quadra q);

/*
*   deleta a quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra
*   nao retorna nada
*/
void removeQuadra(Quadra q);

/*
*   pega o objeto ponto contido na Quadra
*   necessita do ponteiro para objeto do tipo Quadra
*   retorna o objeto ponto que contem as coordenadas do objeto tipo Quadra recebido
*/
ponto retornaQuadraCoord(Quadra q);

/*
*   altera a cor da borda da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra e da nova cor da borda
*   nao retorna nada
*/
void alteraQuadra_Corb(Quadra q, char *corb);

/*
*   altera a cor da sombra da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra e da nova cor da borda
*   nao retorna nada
*/
void alteraQuadra_CorSombra(Quadra q, char *cors);

/*
*   altera a cor de preenchimento da quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra e da nova cor da borda
*   nao retorna nada
*/
void alteraQuadra_Corp(Quadra q, char *corp);

/*
*   adiciona 'numCasos' ao numero total de casos de uma face de uma quadra recebida
*   necessita do ponteiro para objeto do tipo Quadra , sua face e o numero casos a ser adicionado
*   nao retorna nada
*/
void addCasosCovid(Quadra q, char *face, int numCasos);

/*
*   retorna o numero de casos relacionados a face de uma certa face da quadra recebida 
*   necessita da quadra e de sua face
*/
int numCasosFace(Quadra q, char *face);
