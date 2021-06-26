#ifndef str_h
#define str_h

typedef void *String;

/*
*   cria um objeto do tipo String
*   necessita de uma string
*   retorna o ponteiro para o objeto tipo String
*/
String montaString(char *s);

/*
*   altera a string contida no objeto String recebido
*   nao retorna nada
*/
void alteraString(String s, char *novaString);

/*
*   retorna a string contina no objeto String recebido
*/
char *getString(String s);

/*
*   deleta o objeto String recebido
*   nao retorna nada
*/
void removeString(String s);

#endif