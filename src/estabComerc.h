#ifndef estabComerc_h
#define estabComerc_h

#include "pessoa.h"
#include "ponto.h"
#include "retangulo.h"
#include "quadra.h"

typedef void *estabComercial;

/*
*   cria um objeto do tipo estabComercial 
*   necessita das informacoes do estabelecimento, de um objeto do tipo Pessoa e de um objeto do tipo Quadra
*   retorna o ponteiro para o objeto de tipo estabComercial
*/
estabComercial montaEstab(Pessoa p, Quadra quadra, char face, int num, char *cnpj, char *codt, char *nome);

/*
*   altera o endereco do estabelecimento
*   necessita de um objeto do tipo Quadra (destino), de um objeto do tipo estabComercial e da nova face e num
*   nao retorna nada
*/
void alteraEstab_Endereco(estabComercial est, Quadra quadra, char face, int num);

/*
*   deleta o estabelecimento comercial
*   necessita de um objeto do tipo estabComercial
*   nao retorna nada
*/
void removeEc(estabComercial est);

/*
*   pega o objeto do tipo Pessoa do estabelecimento comercial
*   necessita de um objeto do tipo estabComercial
*   retorna ponteiro para o objeto de tipo Pessoa
*/
Pessoa getEstab_Pessoa(estabComercial est);

/*
*   pega o objeto do tipo ponto, contido no estabelecimento comercial, que contem suas coordenadas
*   necessita de um objeto do tipo estabComercial
*   retorna ponteiro para o objeto de tipo ponto
*/
ponto getEstab_Ponto(estabComercial est);

/*
*   pega o Cnpj do estabelecimento comercial
*   necessita de um objeto do tipo estabComercial
*   retorna seu Cnpj (string)
*/
char *getEstab_Cnpj(estabComercial est);

/*
*   pega o Cep do estabelecimento comercial
*   necessita de um objeto do tipo estabComercial
*   retorna seu Cep (string)
*/
char *getEstab_Cep(estabComercial est);

/*
*   pega o nome do estabelecimento comercial
*   necessita de um objeto do tipo estabComercial
*   retorna seu nome (string)
*/
char *getEstab_Nome(estabComercial est);

/*
*   pega a face do estabelecimento comercial
*   necessita de um objeto do tipo estabComercial
*   retorna sua face (char)
*/
char getEstab_Face(estabComercial est);

/*
*   pega o numero do estabelecimento comercial
*   necessita de um objeto do tipo estabComercial
*   retorna seu numero (int)
*/
int getEstab_Num(estabComercial est);

/*
*   pega o tipo do estabelecimento comercial
*   necessita de um objeto do tipo estabComercial
*   retorna seu tipo (string)
*/
char *getEstab_Codt(estabComercial est);


#endif