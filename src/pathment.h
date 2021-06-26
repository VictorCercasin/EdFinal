#ifndef pathment_h
#define pathment_h

typedef void *diretorio;
typedef void *Frags;

/*
    Direciona e configura todos os paths lidos como argumentos do programa
*/
diretorio setPaths(int argc, char ** argv);

/* Libera os espaços de memoria utilizados pela estrutura*/
void free_paths(diretorio caminhos);

/*
*   pega o nome do arquivo qry
*   necessita da lista de caminhos
*   retorna o nome do arquivo qry
*/
char *path_nomeArqQry(diretorio caminhos);

/*
*   pega o nome do arquivo geo
*   necessita da lista de caminhos
*   retorna o nome do arquivo geo
*/
char *path_nomeArqGeo(diretorio caminhos);

/*
*   pega o path do arquivo geo
*   necessita da lista de caminhos
*   retorna a path do arquivo geo
*/
char *path_pathGeo(diretorio caminhos);

/*
*   pega a path do arquivo qry
*   necessita da lista de caminhos
*   retorna a path do arquivo qry
*/
char *path_pathQry(diretorio caminhos);

/*
*   pega a path do arquivo svg do geo
*   necessita da lista de caminhos
*   retorna a path do arquivo svg do geo
*/
char *path_pathSvg_geo(diretorio caminhos);

/*
*   pega a path do arquivo svg do qry
*   necessita da lista de caminhos
*   retorna a path do arquivo svg do qry
*/
char *path_pathSvg_qry(diretorio caminhos);

/*
*   pega a path do arquivo txt
*   necessita da lista de caminhos
*   retorna a path do arquivo txt
*/
char *path_pathTxt(diretorio caminhos);

char *path_Via(diretorio caminhos);

/*
*   retorna o caminho do arquivo ec a partir do ponteiro para objeto diretorio
*/
char *path_Ec(diretorio caminhos);

/*
*   retorna o caminho do arquivo pm a partir do ponteiro para objeto diretorio
*/
char *path_Pm(diretorio caminhos);

// verifica se é necessario criar uma nova path de arquivo svg/txt com sufixo e, caso seja necessário, cria a path
char *criarPathAuxiliar(char *path, char *pathAuxiliar, char *sufixo);

/*
*   concatena o sufixo recebido com a saida do arquivo qry (SVG ou TXT) para criar a path de um outro arquivo
*/
char *concatenaSufixo(char *saidaQry, char *sufixo, char *tipo);

#endif