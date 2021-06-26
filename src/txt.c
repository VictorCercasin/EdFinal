
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "txt.h"
#include "quadra.h"

void criarTxt(char *path){
        FILE *file = fopen(path,"w");

        fclose(file);
}

void escreveTxt(char *path, char info[][50], int qtd){
        FILE *file = fopen(path, "a+");
        int i = 0;

        info[qtd-1][strlen(info[qtd-1])-1]='\0';

        while (i < qtd)
        {
                fprintf(file, "%s ", info[i]);
                i++;
        }
        fprintf(file, "\n");

        fclose(file);
}

void imprimeElemento(char *path, nodulo elemento){
        FILE *arq = fopen(path, "a+");

        Info info = getInfoQt(NULL,elemento);
        Modulo objeto = getModulo(info);
        

        if(strcmp(retornaTipo(info),"rb")==0 || strcmp(retornaTipo(info),"h")==0 || strcmp(retornaTipo(info),"s")==0){
                fprintf(arq, "ID: %s Tipo: %s Coordenadas: X=%lf Y=%lf\n", retornaCirc_Id(objeto), retornaTipo(info), retornaCirc_X(objeto), retornaCirc_Y(objeto));
        }
        else if(strcmp(retornaTipo(info),"q")==0){
                fprintf(arq, "CEP: %s Tipo: %s Coordenadas: X=%lf Y=%lf\n", retornaQuadra_Cep(objeto), retornaTipo(info), retornaQuadra_X(objeto), retornaQuadra_Y(objeto));
        }

        fclose(arq);
}

void oTxt(char *path, nodulo node1, nodulo node2, char *resultado){

        Info info = getInfoQt(NULL,node1);
        Info info2 = getInfoQt(NULL,node2);

        FILE *file = fopen(path, "a+");

        fprintf(file, "%s: %s  %s: %s  %s\n", retornaPos(info), retornaTipo(info), retornaPos(info2), retornaTipo(info2), resultado);
        fclose(file);
}

void iTxt(char *path, nodulo node, char *resultado){

        Info info = getInfoQt(NULL,node);
        FILE *file = fopen(path, "a+");

        fprintf(file, "%s: %s %s\n", retornaPos(info), retornaTipo(info), resultado);
        fclose(file);
}

void pntTxt(char *path, Info info){

        //Info info = getInfoQt(node);
        Modulo elemento = getModulo(info);

        FILE *file = fopen(path, "a+");

        
        if(strcmp(retornaTipo(info),"c")==0){ 
                fprintf(file, "%s: cx=%lf cy=%lf  ", retornaPos(info), retornaCirc_X(elemento), retornaCirc_Y(elemento));
        }
        else if(strcmp(retornaTipo(info),"r")==0){
                fprintf(file, "%s: x=%lf y=%lf  ", retornaPos(info), retornaRet_X(elemento), retornaRet_Y(elemento));
        }
        else if(strcmp(retornaTipo(info),"cv")==0){
                fprintf(file, "cv: x=%lf y=%lf dentro da regiao", retornaCasa_X(elemento), retornaCasa_Y(elemento));
        }
        else{
                fprintf(file, "%s: x=%lf y=%lf  ", retornaPos(info), retornaTexto_X(elemento), retornaTexto_Y(elemento));
        }

        fprintf(file,"\n");

        fclose(file);
}

void pontoTxt(char *path, ponto p){
        FILE *file = fopen(path, "a+");

        fprintf(file, "ps: x = %lf y = %lf, posto de saude proximo\n", retornaPonto_X(p), retornaPonto_Y(p));
        fprintf(file,"\n");
        
        fclose(file);
}

void comandoCiTxt(char *path, long double area, int numCasos, double incidencia){
        FILE *file = fopen(path,"a+");

        fprintf(file, "Area do poligono em km quadrados: %Lf\n",area);
        fprintf(file, "Numero de casos: %d\n", numCasos);

        char categoria;

        if(incidencia < 0.1){
                categoria = 'A';
        }
        else if(incidencia < 5){
                categoria = 'B';
        }
        else if(incidencia < 10){
                categoria = 'C';
        }
        else if(incidencia < 20){
                categoria = 'D';
        }
        else{
                categoria = 'E';
        }

        fprintf(file,"Categoria: %c", categoria);


        fprintf(file,"\n");
        fclose(file);

}

void completarTxt(char *path){
        FILE *file = fopen(path, "a+");

        fprintf(file,"\n");
        fclose(file);
}

void estabTxt(char *pathTXT, Modulo ec, char *desc){
        FILE *file = fopen(pathTXT, "a+");

        Pessoa p = getEstab_Pessoa(ec);

        fprintf(file, "[Estabelecimento] Tipo: %s Descrição: %s \nNome: %s Endereço: %s %c %d\n", getEstab_Codt(ec), desc, getEstab_Nome(ec), getEstab_Cep(ec),getEstab_Face(ec),getEstab_Num(ec));
        fprintf(file, "[Proprietário] Nome: %s %s CPF: %s Data nascimento: %s\n", retornaPessoa_Nome(p), retornaPessoa_Sobrenome(p), retornaPessoa_Cpf(p), retornaPessoa_Nasc(p));
  
        fprintf(file,"\n");
        
        fclose(file);
}

void mudancaTxt(char *pathTXT, Modulo mAntigo, char *cep, char face, int num, char *compl){

        FILE *file = fopen(pathTXT, "a+");

        Pessoa pAntigo = retornaMorador_Pessoa(mAntigo);

        fprintf(file, "Nome: %s %s CPF: %s Data nascimento: %s\n", retornaPessoa_Nome(pAntigo), retornaPessoa_Sobrenome(pAntigo), retornaPessoa_Cpf(pAntigo), retornaPessoa_Nasc(pAntigo));

        fprintf(file, "[Endereco antigo]\n");
        fprintf(file, "Endereço: %s %c %d %s\n\n", retornaMorador_Cep(mAntigo),retornaMorador_Face(mAntigo),retornaMorador_Num(mAntigo),retornaMorador_Compl(mAntigo));

        fprintf(file, "[Endereco novo]\n");
        fprintf(file, "Endereço: %s %c %d %s\n", cep, face, num, compl);

        fprintf(file,"\n");
        
        fclose(file);
}

void moradorTxt(char *pathTXT, Modulo m){
        FILE *file = fopen(pathTXT, "a+");

        Pessoa p = retornaMorador_Pessoa(m);

        fprintf(file, "Nome: %s %s CPF: %s Data nascimento: %s\n", retornaPessoa_Nome(p), retornaPessoa_Sobrenome(p), retornaPessoa_Cpf(p), retornaPessoa_Nasc(p));
        fprintf(file, "Endereço: %s %c %d %s\n", retornaMorador_Cep(m),retornaMorador_Face(m),retornaMorador_Num(m),retornaMorador_Compl(m));

        
        fprintf(file,"\n");
        
        fclose(file);
}

void delfTxt(char *path, Info info){

        Modulo elemento = getModulo(info);

        FILE *file = fopen(path, "a+");

        if (strcmp(retornaTipo(info),"c") == 0 || strcmp(retornaTipo(info),"rb") ==0 || strcmp(retornaTipo(info),"s")==0 || strcmp(retornaTipo(info), "h")==0){  // retornaTipo(elemento) == 'c'
                fprintf(file, "%s: %s r=%lf cx=%lf cy=%lf corb=%s corp=%s  ", retornaCirc_Id(elemento), retornaTipo(info) ,retornaCirc_Raio(elemento), retornaCirc_X(elemento), retornaCirc_Y(elemento), retornaCirc_Corb(elemento), retornaCirc_Corp(elemento));
        }
        
        else if (strcmp(retornaTipo(info),"r") == 0){
                fprintf(file, "%s: %s w=%lf h=%lf x=%lf y=%lf corb=%s corp=%s  ", retornaRet_Id(elemento),retornaTipo(info), retornaRet_W(elemento), retornaRet_H(elemento), retornaRet_X(elemento), retornaRet_Y(elemento), retornaRet_Corb(elemento), retornaRet_Corp(elemento));
        }

        else if (strcmp(retornaTipo(info),"q")==0){
                fprintf(file, "%s: %s w=%lf h=%lf x=%lf y=%lf corb=%s corp=%s  ", retornaQuadra_Cep(elemento), retornaTipo(info), retornaQuadra_W(elemento), retornaQuadra_H(elemento), retornaQuadra_X(elemento), retornaQuadra_Y(elemento), retornaQuadra_Corb(elemento), retornaQuadra_Corp(elemento));
        }

        else{
                fprintf(file, "%s: texto x=%lf y=%lf corb=%s corp=%s conteudo=%s  ", retornaTexto_Id(elemento), retornaTexto_X(elemento), retornaTexto_Y(elemento), retornaTexto_Corb(elemento), retornaTexto_Corp(elemento), retornaConteudo(elemento));
        }

        fprintf(file,"\n");
        
        fclose(file);
}