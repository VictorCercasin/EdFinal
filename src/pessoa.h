#ifndef pessoa_h
#define pessoa_h

typedef void *Pessoa;

/*
*   cria um objeto do tipo Pessoa
*   necessita das informacoes da pessoa
*   retorna o ponteiro para o objeto tipo Pessoa
*/
Pessoa montaPessoa(char *cpf,char *nome, char *sobrenome, char sexo, char *nasc);

/*
*   pega o cpf do objeto Pessoa
*   necessita de um ponteiro para o objeto Pessoa
*   retorna o cpf (string) da pessoa
*/
char *retornaPessoa_Cpf(Pessoa p);

/*
*   pega o nome do objeto Pessoa
*   necessita de um ponteiro para o objeto Pessoa
*   retorna o nome (string) da pessoa
*/
char *retornaPessoa_Nome(Pessoa p);

/*
*   pega o sobrenome do objeto Pessoa
*   necessita de um ponteiro para o objeto Pessoa
*   retorna o sobrenome (string) da pessoa
*/
char *retornaPessoa_Sobrenome(Pessoa p);

/*
*   pega o sexo do objeto Pessoa
*   necessita de um ponteiro para o objeto Pessoa
*   retorna o sexo (char) da pessoa
*/
char retornaPessoa_Sexo(Pessoa p);

/*
*   pega a data de nascimento do objeto Pessoa
*   necessita de um ponteiro para o objeto Pessoa
*   retorna a data de nascimento (string) da pessoa
*/
char *retornaPessoa_Nasc(Pessoa p);

/*
*   deleta um objeto tipo Pessoa
*   necessita de um ponteiro para o objeto Pessoa
*   nao retorna nada
*/
void removePessoa(Pessoa p);

#endif