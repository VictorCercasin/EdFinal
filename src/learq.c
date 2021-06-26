#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "learq.h"
#include "str.h"
#include "quadra.h"
#include "svg.h"
#include "str.h"

int funcLer(char *line, char mat[][50]){

        char *token;
        int i=0;

        token = strtok(line," ");

        while(token != NULL){
                strcpy(mat[i],token);
                token = strtok(NULL," ");
                i++;
        }

        return i;
}

void lerArqGeo(char *arq, HashTable cepXquadra, QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree quadras, QuadTree torresCelular, QuadTree semaforos, QuadTree postos, QuadTree regioes){
        
        int i=1000, nq=1000, nh=1000, ns=1000, nr=1000;

        double x, y, r, h, w, d;
        char input[100], conteudo[300], Id[100];// Id/CEP

        //Default
        char Fig_cfill[100], Fig_cstrk[100], cw[100]="1", rw[100]="1";
        char Quad_cfill[100]="orange", Quad_cstrk[100]="orange", Quad_sw[100]="1";
        char Semaf_cfill[100]="blue", Semaf_cstrk[100]="blue", Semaf_sw[100]="1";
        char Hid_cfill[100]="red", Hid_cstrk[100]="red", Hid_sw[100]="1";
        char radT_cfill[100]="green", radT_cstrk[100]="green", radT_sw[100] = "1";

        FILE* arqGeo = fopen(arq, "r"); // arq = path_pathGeo(dir)

        Lista circulosLista = criarLista();
        Lista retangulosLista = criarLista();
        Lista textosLista = criarLista();
        Lista hidrantesLista = criarLista();
        Lista quadrasLista = criarLista();
        Lista torresCelLista = criarLista();
        Lista semaforosLista = criarLista();
        Lista postosLista = criarLista();
        Lista regioesLista = criarLista();

        int cont=0;

        while(!feof(arqGeo)){

                fscanf(arqGeo,"%s",input);

                if(strcmp(input,"nx")==0){
                        fscanf(arqGeo,"%d %d %d %d %d\n",&i, &nq, &nh, &ns, &nr);
                }

                else if(strcmp(input,"c")==0){
                        fscanf(arqGeo,"%s %lf %lf %lf %s %s\n",Id, &r, &x, &y, Fig_cstrk, Fig_cfill);

                        circulo circ = montaCirculo(Id, cw,r, x, y, Fig_cstrk, Fig_cfill);
                        Info info = montaInfo("circulo",Id,circ);
                        
                        ponto p = retornaCircCoord(circ);

                        insertAfterLast(circulosLista, info);
                }

                else if(strcmp(input,"r")==0){

                        fscanf(arqGeo,"%s %lf %lf %lf %lf %s %s\n",Id , &w, &h, &x, &y, Fig_cstrk, Fig_cfill);

                        retangulo ret = montaRetangulo(Id, rw, w, h, x, y, Fig_cstrk, Fig_cfill);
                        Info info = montaInfo("r",Id,ret);

                
                        ponto p = retornaRetCoord(ret);
                        
                        insertAfterLast(retangulosLista, info);
                }

                else if(strcmp(input, "t")==0){
                        fscanf(arqGeo,"%s %lf %lf %s %s\n",Id, &x, &y, Fig_cstrk, Fig_cfill);

                        fgets(conteudo, 300, arqGeo);
                        fscanf(arqGeo,"\n");
                        conteudo[strlen(conteudo)] = '\0';


                        int len = strlen(conteudo)+1;

                        texto text = montaTexto(Id,x,y,Fig_cstrk,Fig_cfill,conteudo,len);
                        Info info = montaInfo("t",Id,text);

                        ponto p = retornaTextoCoord(text);
          
                        insertAfterLast(textosLista, info);
                }
                
                else if(strcmp(input,"q")==0){
                        fscanf(arqGeo,"%s %lf %lf %lf %lf\n",Id, &x, &y, &w, &h);

                        Quadra quad = montaQuadra(Id, Quad_sw, w, h, x, y, Quad_cstrk, Quad_cfill);
                        Info info = montaInfo("q",Id,quad);

                        insertAfterLast(quadrasLista, info);
                        insereHT(cepXquadra, Id, info);
                }

                else if(strcmp(input,"h")==0){
                        fscanf(arqGeo,"%s %lf %lf\n",Id, &x, &y);

                        circulo hid = montaCirculo(Id, Hid_sw, 5, x, y, Hid_cstrk, Hid_cfill);
                        Info info = montaInfo("h",Id,hid);

                        ponto p = retornaCircCoord(hid);
                        
                        insertAfterLast(hidrantesLista, info);
                }

                else if(strcmp(input,"s")==0){
                        fscanf(arqGeo,"%s %lf %lf\n",Id, &x, &y);

                        circulo semaf = montaCirculo(Id, Semaf_sw, 5, x, y, Semaf_cstrk, Semaf_cfill);
                        Info info = montaInfo("s",Id,semaf);

                        ponto p = retornaCircCoord(semaf);
                        
                        insertAfterLast(semaforosLista, info);
                }
                
                else if(strcmp(input,"rb")==0){
                        fscanf(arqGeo,"%s %lf %lf\n",Id, &x, &y);

                        circulo torreCel = montaCirculo(Id, radT_sw, 5, x, y, radT_cstrk, radT_cfill);
                        Info info = montaInfo("rb",Id,torreCel);

                        ponto p = retornaCircCoord(torreCel);
                
                        insertAfterLast(torresCelLista, info);
                }

                else if(strcmp(input,"cq")==0){
                        fscanf(arqGeo,"%s %s %s\n", Quad_sw, Quad_cfill, Quad_cstrk);
                }
                
                else if(strcmp(input,"ch")==0){
                        fscanf(arqGeo,"%s %s %s\n", Hid_sw, Hid_cfill, Hid_cstrk);
                }

                else if(strcmp(input,"cr")==0){
                        fscanf(arqGeo,"%s %s %s\n", radT_sw, radT_cfill, radT_cstrk);
                }

                else if(strcmp(input,"cs")==0){
                        fscanf(arqGeo,"%s %s %s\n", Semaf_sw, Semaf_cfill, Semaf_cstrk);
                }

                else if(strcmp(input,"sw")==0){
                        fscanf(arqGeo,"%s %s\n", cw, rw);
                }

                else if(strcmp(input,"ps")==0){
                        fscanf(arqGeo,"%lf %lf\n", &x, &y);

                        ponto p = montaPonto(x, y);
                        Info info = montaInfo("ps","null",p);

                        insertAfterLast(postosLista, info);
                }

                else if(strcmp(input,"dd")==0){
                        fscanf(arqGeo,"%lf %lf %lf %lf %lf\n", &x, &y, &w, &h, &d);

                        regiao reg = montaRegiao(x, y, w, h, d); 
                        Info info = montaInfo("dd","null",reg);

                        ponto p = retornaRegiaoCoord(reg);
                        
                        insertAfterLast(regioesLista, info);
      
                }

        }

        carregarSombraQuadras(quadrasLista,regioesLista);

        ordenaInsercaoQt(circulos,circulosLista);
        limparLista_aux(circulosLista);

        ordenaInsercaoQt(retangulos,retangulosLista);
        limparLista_aux(retangulosLista);

        ordenaInsercaoQt(textos,textosLista);
        limparLista_aux(textosLista);

        ordenaInsercaoQt(hidrantes,hidrantesLista);
        limparLista_aux(hidrantesLista);

        ordenaInsercaoQt(quadras,quadrasLista);
        limparLista_aux(quadrasLista);

        ordenaInsercaoQt(torresCelular,torresCelLista);
        limparLista_aux(torresCelLista);

        ordenaInsercaoQt(semaforos,semaforosLista);
        limparLista_aux(semaforosLista);

        ordenaInsercaoQt(postos,postosLista);
        limparLista_aux(postosLista);

        ordenaInsercaoQt(regioes,regioesLista);
        limparLista_aux(regioesLista);

        fclose(arqGeo);
}


void lerArqPm(char *arq, Lista moradores, HashTable cpfXpessoa, HashTable cepXquadra, HashTable cpfXcep){
        
        FILE* arqPm = fopen(arq, "r");
        char cpf[100], nome[100], sobrenome[100], sexo, nasc[100], cep[100], compl[100], face;
        int num;
        char input[100];

        while(!feof(arqPm)){
                
                fscanf(arqPm,"%s",input);

                if(strcmp(input,"p")==0){

                        fscanf(arqPm,"%s %s %s %c %s", cpf, nome, sobrenome, &sexo, nasc);
                    
                        Pessoa p = montaPessoa(cpf,nome,sobrenome,sexo,nasc);
                        Info info = montaInfo("pessoa",cpf,p);
                        
                        insereHT(cpfXpessoa, cpf, info);
                }

                if(strcmp(input,"m")==0){

                        fscanf(arqPm,"%s %s %c %d %s", cpf, cep, &face, &num, compl);

                        String str = montaString(cep);
                        Info infoCep = montaInfo("str",cpf,str);

                        insereHT(cpfXcep,cpf,infoCep);

                        Info infoPessoa = searchHash(cpfXpessoa,cpf);
                        if(infoPessoa == NULL){
                                continue;
                        }
                        Pessoa p = getModulo(infoPessoa);

                        Info infoQuadra = searchHash(cepXquadra,cep);
                        if(infoQuadra == NULL){
                                continue;
                        }

                        Quadra quadra = getModulo(infoQuadra);

                        Morador m = montaMorador(p, quadra, face, num, compl);
                        Info info = montaInfo("morador",cpf,m);
                        
                        insertAfterLast(moradores,info);
                }

        }

        fclose(arqPm);
}


void lerArqEc(char *arq, HashTable codtXdesc, HashTable cpfXpessoa, Lista estabComerc, HashTable cepXquadra){

        FILE* arqEc = fopen(arq, "r");

        int num;
        char input[100], cep[100], face, cnpj[100], cpf[100], desc[100], codt[100], nome[100];

        while(!feof(arqEc)){

                fscanf(arqEc,"%s",input);

                if(strcmp(input,"t")==0){

                        fscanf(arqEc,"%s %s", codt, desc);

                        String str = montaString(desc);
                        Info info = montaInfo("str",codt,str);

                        insereHT(codtXdesc, codt, info);
                }

                if(strcmp(input,"e")==0){

                        fscanf(arqEc,"%s %s %s %s %c %d %s", cnpj, cpf, codt, cep, &face, &num, nome);

                        Info infoPessoa = searchHash(cpfXpessoa,cpf);
                        if(infoPessoa == NULL){
                                continue;
                        }

                        Pessoa p = getModulo(infoPessoa);

                        
                        Info infoQuadra = searchHash(cepXquadra,cep);
                        if(infoQuadra == NULL){
                                continue;
                        }

                        Quadra quadra = getModulo(infoQuadra);

                        estabComercial ec = montaEstab(p, quadra, face, num, cnpj, codt, nome);
                        Info info = montaInfo("ec",codt,ec);

                        insertAfterLast(estabComerc, info);
                }


        }


        fclose(arqEc);
}

int insereVerticesNaListaAdjacencia(Grafo grafo,QtNo vertices, int posicaoVertice){
    
    if(vertices == NULL)  return posicaoVertice;

    if(isCleared(vertices) == 0){

        Info verticeInfo = getInfoQt(NULL,vertices);
        ModuloVertice vertice = getModulo(verticeInfo);
        ponto coord = retornaVerticeCoord(vertice);
        HashTable idvXi = retornaHashTableGrafo(grafo);

        char *idv = retornaVerticeId(vertice);
        
        insereVertice(grafo, posicaoVertice, vertice); 

        int *inteiro = malloc(sizeof(int));
        *inteiro = posicaoVertice;
        Info infoInteiro = montaInfo("inteiro",idv,inteiro);
        insereHT(idvXi, idv, infoInteiro);

        posicaoVertice += 1;
    }

    posicaoVertice = insereVerticesNaListaAdjacencia(grafo, getSE(vertices), posicaoVertice);
    posicaoVertice = insereVerticesNaListaAdjacencia(grafo, getNE(vertices), posicaoVertice);
    posicaoVertice = insereVerticesNaListaAdjacencia(grafo, getSW(vertices), posicaoVertice);
    posicaoVertice = insereVerticesNaListaAdjacencia(grafo, getNW(vertices), posicaoVertice);
}

Grafo lerArqVia(char *arq){

        FILE* arqVia = fopen(arq, "r");

        Grafo *grafo= NULL;
        int grafoCriado = 0;

        //Cria Hashtable
        HashTable idvXi = criaHt(80);

        //Variaveis da aresta e vertice
        char input[100], id[100], ldir[100], lesq[100], v1[100],v2[100], nomeRua[100];
        double comprimento, velocidadeMedia, x,y;

        //Cria arvore auxiliar
        QuadTree verticesQt = criaQt(retornaVerticeId);
        
        while(!feof(arqVia)){
                
                fscanf(arqVia,"%s",input);

                if(strcmp(input,"v")==0){

                        fscanf(arqVia,"%s %lf %lf", id, &x, &y);
                        
                        ponto coord = montaPonto(x,y);
                        ModuloVertice vertice = criaVertice(id, coord);
                        Info infoVertice = montaInfo("vertice", id, vertice);

                        insereQt(verticesQt, coord, infoVertice);
                }

                if(strcmp(input,"e")==0){

                        if(grafoCriado==0){
                                int tamanho = getQt_ObjAmount(verticesQt);
                                grafo = criaGrafo(tamanho, idvXi, verticesQt);
                                insereVerticesNaListaAdjacencia(grafo,getNoQt_root(verticesQt),0);
                                grafoCriado = 1;
                        }

                        fscanf(arqVia,"%s %s %s %s %lf %lf %s", v1, v2, ldir, lesq, &comprimento, &velocidadeMedia, nomeRua);

                        if(searchHash(idvXi, v1)!=NULL && searchHash(idvXi, v2)!=NULL){
                                int *posicaoInicial = getModulo(searchHash(idvXi, v1));
                                int *posicaoFinal = getModulo(searchHash(idvXi, v2));
                                insereAresta(grafo, *posicaoInicial, *posicaoFinal, ldir, lesq, nomeRua, velocidadeMedia, comprimento);
                        }
                }
        }

        fclose(arqVia);
        return grafo;
}
