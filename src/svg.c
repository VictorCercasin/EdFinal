#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadtree.h"
#include "svg.h"
#include "leqry.h"
#include "regiao.h"

int idPath = 1;

void transfListasSVG(FILE *fileSVG,Lista listQRY, Lista poligonos){

        nodulo nodeQRY = getFirst(listQRY);
        nodulo nodePoly = getFirst(poligonos);

        fprintf(fileSVG,"<svg>");

        if(nodeQRY!=NULL){
                escreveSVG(fileSVG, listQRY);
        }

        if(nodePoly){
                escreveSVG(fileSVG,poligonos);
        }

        fprintf(fileSVG,"\n</svg>");
}


void selecionaTipoSVG(Info info, void *file){
        
        FILE* fileSVG = (FILE*)file;
        Modulo figura = getModulo(info);
        
        if(strcmp(retornaTipo(info),"r") == 0){             
                insereRetangulo(fileSVG,figura);
        } 
        else if(strcmp(retornaTipo(info),"c") == 0){
                insereCirculo(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"circulo") == 0){
                insereCirculoC(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"t") == 0){
                insereTexto(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"l") == 0){
                insereLinha(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"d") == 0){
                insereRetTracado(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"e") == 0){
                insereRetLine(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"q") == 0){
                insereQuadra(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"h")==0){
                insereHidrante(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"s")==0){
                insereSemaforo(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"rb")==0){
                insereTorreCel(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"rA")==0){
                insereRetArredondado(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info), "ps")==0){
                inserePosto(fileSVG, figura);
        }
        else if(strcmp(retornaTipo(info),"cv")==0){
                insereCasa(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"poly")==0){
                inserePoligono(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"lt")==0){
                insereLinhaTracejada(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"pontoEc")==0){
                insereEstab(fileSVG,figura);
        }
        else if(strcmp(retornaTipo(info),"pontoCor")==0){
                inserePontoGen(fileSVG,info);
        }
        else if(strcmp(retornaTipo(info),"circCalac")==0){
                insereCircCalac(fileSVG,figura);
        }
}

void carregaCircCalac(Lista list, double x, double y, double r, char *corp, char *corb){
        
        circulo c = montaCirculo("-123","2", r, x, y, corb, corp);
        Info infoCirc = montaInfo("circCalac","null",c);

        insertAfterLast(list,infoCirc);
}

void insereCircCalac(FILE *path, Modulo c){

        fprintf(path,"\n");

        fprintf(path,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\" stroke=\"%s\" fill-opacity=\"0.5\" stroke-width=\"%s\" />\n", retornaCirc_X(c), retornaCirc_Y(c), retornaCirc_Raio(c), retornaCirc_Corp(c),retornaCirc_Corb(c),retornaCirc_SW(c));
}


void inserePontoGen(FILE *path, Info info){
        fprintf(path,"\n");

        Modulo p = getModulo(info);
        
        fprintf(path,"<circle cx= \"%lf\" cy=\"%lf\" r=\"2\" stroke=\"white\" stroke-width=\"1\" fill=\"%s\"/>\n",retornaPonto_X(p), retornaPonto_Y(p), retornaPos(info)); 
}

void transfSVG(FILE *fileSVG, Lista listQRY, Lista poligonos, QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree quadras, QuadTree radioTorres, QuadTree semaforos, QuadTree pontos, Lista casas){
        fprintf(fileSVG,"<svg>");
        //fprintf(fileSVG,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n<svg viewBox=\"-150 -150 15000 15000\" style=\"width: 20000px; height: 20000px\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">");
        
        percorreProfundidadeQt(circulos,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(retangulos,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(textos,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(quadras,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(hidrantes,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(radioTorres,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(semaforos,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(pontos,selecionaTipoSVG,(void*)fileSVG);

        escreveSVG(fileSVG, casas);
        escreveSVG(fileSVG, listQRY);
        escreveSVG(fileSVG, poligonos);

        fprintf(fileSVG,"\n</svg>");
}

void transfSVGgeo(FILE *fileSVG, QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree quadras, QuadTree radioTorres, QuadTree semaforos, QuadTree pontos){
        
        fprintf(fileSVG,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n<svg viewBox=\"-150 -150 15000 15000\" style=\"width: 20000px; height: 20000px\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">");

        percorreProfundidadeQt(circulos,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(retangulos,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(textos,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(quadras,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(hidrantes,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(radioTorres,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(semaforos,selecionaTipoSVG,(void*)fileSVG);
        percorreProfundidadeQt(pontos,selecionaTipoSVG,(void*)fileSVG);
        
}

void escreveSVG(FILE *fileSVG, Lista lista){

        nodulo node = getFirst(lista);

        if(node==NULL){
                return;
        }

        Info info;
        Modulo figura;        

        while(node!=NULL){
                info = getInfo(node);
                figura = getModulo(getInfo(node));

                selecionaTipoSVG(info,(void*)fileSVG);

                node = getNext(node);
        }

}

void inserePoligono(FILE *path, Modulo poly){

        fprintf(path,"\n");

        int n = retornaPoligono_Tam(poly);

        ponto *array = retornaArrayPontos(poly);

        fprintf(path,"<polygon points=\" ");

        for(int i=0;i<n;i++){
                fprintf(path,"%lf,%lf ", retornaPonto_X(array[i]),retornaPonto_Y(array[i]));
        }
        
        fprintf(path,"\" fill-opacity=\"0.6\" fill=\"%s\" stroke=\"red\" stroke-width=\"1\"/>\n", retornaPoligono_Cor(poly));

}

void insereCasa(FILE *path, Modulo c){

        fprintf(path,"\n");

        fprintf(path,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"orange\" stroke=\"orange\" stroke-width=\"1\"/>\n", retornaCasa_X(c), retornaCasa_Y(c), retornaCasa_W(c), retornaCasa_H(c));

        fprintf(path,"<text x=\"%lf\"  y=\"%lf\" stroke=\"white\" fill= \"white\" font-size=\"6\" text-anchor= \"middle\">%d</text>\n", retornaCasa_Nx(c), retornaCasa_Ny(c), retornaCasa_N(c));

}

void insereEstab(FILE *path, Modulo ec){

        fprintf(path,"\n");

        fprintf(path,"<circle cx= \"%lf\" cy=\"%lf\" r=\"3\" stroke=\"orange\" stroke-width=\"1\" fill=\"black\"/>\n",retornaPonto_X(ec), retornaPonto_Y(ec)); 
}


void inserePosto(FILE *path, Modulo p){

        fprintf(path,"\n");


        fprintf(path,"<polygon fill=\"rgb(255,0,0)\"  stroke-width=\"3\" stroke-miterlimit=\"10\" points=\"%lf %lf, %lf %lf, %lf %lf, %lf %lf,\"/>\n", retornaPonto_X(p)-5, retornaPonto_Y(p), retornaPonto_X(p), retornaPonto_Y(p)-5,retornaPonto_X(p)+5, retornaPonto_Y(p), retornaPonto_X(p), retornaPonto_Y(p)+5); 
        fprintf(path,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,255,255);stroke-width:1\" />\n", retornaPonto_X(p)-5, retornaPonto_Y(p), retornaPonto_X(p)+5, retornaPonto_Y(p)); 
        fprintf(path,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,255,255);stroke-width:1\" />\n",retornaPonto_X(p), retornaPonto_Y(p)-5, retornaPonto_X(p), retornaPonto_Y(p)+5); 
}

void insereRetArredondado(FILE *path,Modulo retArred){

        fprintf(path,"\n");

        fprintf(path,"<rect x=\"%lf\" y=\"%lf\" rx=\"10\" ry=\"10\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\" />\n", retornaRet_X(retArred), retornaRet_Y(retArred), retornaRet_W(retArred), retornaRet_H(retArred), retornaRet_Corp(retArred), retornaRet_Corb(retArred), retornaRet_SW(retArred));

}

void insereQuadra(FILE *path, Modulo quad){      
        
        fprintf(path,"\n");

        fprintf(path,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\" />\n", retornaQuadra_X(quad)+3, retornaQuadra_Y(quad)+3, retornaQuadra_W(quad), retornaQuadra_H(quad), retornaQuadra_CorSombra(quad), retornaQuadra_CorSombra(quad), retornaQuadra_SW(quad));
        fprintf(path,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\" />\n", retornaQuadra_X(quad), retornaQuadra_Y(quad), retornaQuadra_W(quad), retornaQuadra_H(quad), retornaQuadra_Corp(quad), retornaQuadra_Corb(quad), retornaQuadra_SW(quad));
}

void insereHidrante(FILE *path, Modulo hid){
              
        fprintf(path,"\n");

        fprintf(path,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\" />\n", retornaCirc_X(hid), retornaCirc_Y(hid), retornaCirc_Raio(hid), retornaCirc_Corp(hid),retornaCirc_Corb(hid),retornaCirc_SW(hid));
}

void insereSemaforo(FILE *path, Modulo semaf){
              
        fprintf(path,"\n");

        fprintf(path,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\" />\n", retornaCirc_X(semaf), retornaCirc_Y(semaf), retornaCirc_Raio(semaf), retornaCirc_Corp(semaf),retornaCirc_Corb(semaf),retornaCirc_SW(semaf));

}

void insereTorreCel(FILE *path, Modulo torreCel){
              
        fprintf(path,"\n");

        fprintf(path,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\" />\n", retornaCirc_X(torreCel), retornaCirc_Y(torreCel), retornaCirc_Raio(torreCel), retornaCirc_Corp(torreCel),retornaCirc_Corb(torreCel),retornaCirc_SW(torreCel));
}


void insereCirculo(FILE *path,Modulo circ){

        fprintf(path,"\n");

        fprintf(path,"<circle cx= \"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\"/>",retornaCirc_X(circ), retornaCirc_Y(circ), retornaCirc_Raio(circ), retornaCirc_Corb(circ),retornaCirc_SW(circ),retornaCirc_Corp(circ)); 
 
}

void insereCirculoC(FILE *path,Modulo circ){

        fprintf(path,"\n");

        fprintf(path,"<circle cx= \"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\"/>",retornaCirc_X(circ), retornaCirc_Y(circ), retornaCirc_Raio(circ), retornaCirc_Corb(circ),retornaCirc_SW(circ),retornaCirc_Corp(circ)); 
        fprintf(path,"<circle cx= \"%lf\" cy=\"%lf\" fill-opacity=\"0.25\" r=\"%lf\" stroke=\"%s\" stroke-width=\"%lf\" fill=\"%s\" />",retornaCirc_X(circ), retornaCirc_Y(circ), (retornaCirc_Raio(circ)*0.5),retornaCirc_Corp(circ) ,(transfStringDouble( retornaCirc_SW(circ))/2),retornaCirc_Corb(circ)); 

}



void insereRetangulo(FILE *path,Modulo ret){

        fprintf(path,"\n");

        fprintf(path,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\" />", retornaRet_X(ret), retornaRet_Y(ret), retornaRet_W(ret), retornaRet_H(ret), retornaRet_Corp(ret), retornaRet_Corb(ret), retornaRet_SW(ret));

}

void carregaPonto(Lista lista, double x, double y, char *corp){

        ponto pnt = montaPonto(x,y);
        Info infoPonto = montaInfo("pontoCor",corp,pnt);

        insertAfterLast(lista, infoPonto);
}

void carregaLinha(Lista lista, double x1, double y1, double x2, double y2, char *cor){

        Modulo line = montaRetangulo("-3","3", x1, y1, x2, y2, cor, cor);
        Info infoLine = montaInfo("l","-2", line);

        insertAfterLast(lista, infoLine);
        
}

void insereTexto(FILE *path,Modulo txt){
        
        fprintf(path,"\n");

        fprintf(path,"<text x=\"%lf\"  y=\"%lf\" style=\"stroke:%s;fill:%s;\">%s</text>",retornaTexto_X(txt), retornaTexto_Y(txt), retornaTexto_Corb(txt), retornaTexto_Corp(txt),retornaConteudo(txt));
    
}

void insereLinhaTracejada(FILE *path, Modulo line){
        fprintf(path,"\n");
        fprintf(path,"<line stroke-linecap=\"null\" stroke-dasharray=\"1\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"%s\" fill=\"%s\"/>",retornaRet_Y(line),retornaRet_H(line),retornaRet_X(line),retornaRet_W(line),retornaRet_Corb(line),retornaRet_Corp(line));
}

void insereLinha(FILE *path,Modulo line){

        fprintf(path,"\n");
        fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"%s\" fill=\"%s\"/>",retornaRet_Y(line),retornaRet_H(line),retornaRet_X(line),retornaRet_W(line),retornaRet_Corb(line),retornaRet_Corp(line));

}

void carregaRetTracado(Lista lista, double x, double y, double h, double w){

        Modulo retTrac = montaRetangulo("-3","1",w,h,x,y,NULL,NULL);
        Info info = montaInfo("d","-3",retTrac);

        insertAfterLast(lista, info);

}

void insereRetTracado(FILE *path, Modulo retTrac){
  
        fprintf(path,"\n");
        fprintf(path,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" style=\"stroke:black;stroke-width:3;stroke-dasharray:5,5\" />", retornaRet_X(retTrac), retornaRet_Y(retTrac), retornaRet_W(retTrac), retornaRet_H(retTrac));

}

void carregaRetLine(Lista lista,double x,double y, double h, double w){

        Modulo retLine = montaRetangulo("-4","1",w,h,x,y,NULL,NULL);
        Info info = montaInfo("e","-4",retLine);

        insertAfterLast(lista, info);

}

void insereRetLine(FILE *path, Modulo retLine){

        fprintf(path,"\n");
        fprintf(path,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" style=\"stroke:black;stroke-width:3;\" />", retornaRet_X(retLine), retornaRet_Y(retLine), retornaRet_W(retLine), retornaRet_H(retLine));

}

void imprimirQuadtree_aux(QtNo raiz, FILE *path, char *cor){
        
        if(raiz == NULL)
                return;

        char corProximo[30];

        Info info = getInfoQt(NULL,raiz);
        Modulo objeto = getModulo(info);

        if(strcmp(retornaTipo(info),"q")==0){
                fprintf(path,"<rect x=\"%lf\" y=\"%lf\" width=\"120\" height=\"60\" fill=\"%s\"/>", retornaQuadra_X(objeto), retornaQuadra_Y(objeto), cor);
                fprintf(path,"<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" font-size=\"10\" style=\"fill:black;\">%s</text>", retornaQuadra_X(objeto)+60, retornaQuadra_Y(objeto)+30, retornaQuadra_Cep(objeto));
                fprintf(path,"<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" font-size=\"10\" style=\"fill:black;\">X=%.0lf Y=%.0lf</text>", retornaQuadra_X(objeto)+60, retornaQuadra_Y(objeto)+50, retornaQuadra_X(objeto), retornaQuadra_Y(objeto));
        }// imprime quadra
        else{
                fprintf(path,"<circle cx=\"%lf\" cy=\"%lf\" r=\"3\" fill=\"%s\"/>\n", retornaCirc_X(objeto), retornaCirc_Y(objeto), cor);
                fprintf(path,"<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" font-size=\"1\" style=\"fill:black;\">%s</text>", retornaCirc_X(objeto)+3, retornaCirc_Y(objeto)+5, retornaCirc_Id(objeto));
                fprintf(path,"<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" font-size=\"1\" style=\"fill:black;\">X=%.0lf</text>", retornaCirc_X(objeto)+3, retornaCirc_Y(objeto)+7, retornaCirc_X(objeto));
                fprintf(path,"<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" font-size=\"1\" style=\"fill:black;\">Y=%.0lf</text>", retornaCirc_X(objeto)+3, retornaCirc_Y(objeto)+9, retornaCirc_Y(objeto));
        } // imprime circulo


        if(strcmp(cor,"red") == 0){
                strcpy(corProximo,"yellow");
        }// imprime raiz

        else if(strcmp(cor,"yellow") == 0){
                strcpy(corProximo,"orange");
        }else if(strcmp(cor,"orange") == 0){
                strcpy(corProximo,"brown");
        }else if(strcmp(cor,"brown") == 0){
                strcpy(corProximo,"yellow");
        }

        QtNo nw = getNW(raiz);
        QtNo ne = getNE(raiz);
        QtNo sw = getSW(raiz);
        QtNo se = getSE(raiz);

        if(nw != NULL){ //TEM NW

              info = getInfoQt(NULL,nw);
              ponto pnt = retornaInfoCoord(info);

              if(strcmp(retornaTipo(info),"q")==0){
                fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"black\"/>", retornaPonto_Y(pnt)+30, retornaQuadra_Y(objeto)+30, retornaPonto_X(pnt)+60, retornaQuadra_X(objeto)+60);  
              }else{
                fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"black\"/>", retornaPonto_Y(pnt),retornaCirc_Y(objeto), retornaPonto_X(pnt), retornaCirc_X(objeto));  
              }
              imprimirQuadtree_aux(nw,path,corProximo);  
        }

        if(ne != NULL){ //TEM NE

              info = getInfoQt(NULL,ne);
              ponto pnt = retornaInfoCoord(info);

              if(strcmp(retornaTipo(info),"q")==0){
                fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"black\"/>", retornaPonto_Y(pnt)+30, retornaQuadra_Y(objeto)+30, retornaPonto_X(pnt)+60, retornaQuadra_X(objeto)+60);  
              }else{
                fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"black\"/>", retornaPonto_Y(pnt), retornaCirc_Y(objeto), retornaPonto_X(pnt), retornaCirc_X(objeto));  
              }
              imprimirQuadtree_aux(ne,path,corProximo);  
        }

        if(sw != NULL){ //TEM SW

              info = getInfoQt(NULL,sw);
              ponto pnt = retornaInfoCoord(info);

              if(strcmp(retornaTipo(info),"q")==0){
                fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"black\"/>", retornaPonto_Y(pnt)+30, retornaQuadra_Y(objeto)+30, retornaPonto_X(pnt)+60, retornaQuadra_X(objeto)+60);  
              }else{
                fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"black\"/>", retornaPonto_Y(pnt), retornaCirc_Y(objeto), retornaPonto_X(pnt), retornaCirc_X(objeto));  
              }
              imprimirQuadtree_aux(sw,path,corProximo);  
        }

        if(se != NULL){ //TEM SE

              info = getInfoQt(NULL,se);
              ponto pnt = retornaInfoCoord(info);

              if(strcmp(retornaTipo(info),"q")==0){
                fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"black\"/>", retornaPonto_Y(pnt)+30, retornaQuadra_Y(objeto)+30, retornaPonto_X(pnt)+60, retornaQuadra_X(objeto)+60);  
              }else{
                fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"black\"/>", retornaPonto_Y(pnt), retornaCirc_Y(objeto), retornaPonto_X(pnt), retornaCirc_X(objeto));  
              }
              imprimirQuadtree_aux(se,path,corProximo);  
        }
        
}

void carregarSombraQuadras_aux(Info infoQuadra, double densidade){
       
        Quadra quadra = getModulo(infoQuadra);

        if(densidade>=10 && densidade<500){
                alteraQuadra_CorSombra(quadra,"#FFFF00");
        }

        else if(densidade>=500 && densidade<1500){
                alteraQuadra_CorSombra(quadra,"#FF9955");
        }

        else if(densidade>=1500 && densidade<3000){
                alteraQuadra_CorSombra(quadra,"#FF0000");
        }

        else if(densidade>=3000 && densidade<4500){
                alteraQuadra_CorSombra(quadra,"#FF00CC");
        }

        else if(densidade>=4500 && densidade<6000){
                alteraQuadra_CorSombra(quadra,"#6600FF");
        }
        
        else if(densidade>=6000){
                alteraQuadra_CorSombra(quadra,"#A02C5A");
        }

}

void carregarSombraQuadras(Lista quadras, Lista regioes){

        nodulo node = getFirst(quadras);

        if(listSize(regioes)==0){
                return;
        }

        while(node!=NULL){

                nodulo nodeRegiao = getFirst(regioes);
                Info infoQuadra = getInfo(node);

                while(nodeRegiao!=NULL){

                        Info infoRegiao = getInfo(nodeRegiao);
                        regiao reg= getModulo(infoRegiao);

                        double x = retornaReg_X(reg);
                        double y = retornaReg_Y(reg);
                        double w = retornaReg_W(reg);
                        double h = retornaReg_H(reg);

                        int check = verificaInteriorRet(x, y, x+w,y+h,infoQuadra);

                        if(check==0){
                                carregarSombraQuadras_aux(infoQuadra, retornaReg_D(reg));
                        }

                        nodeRegiao = getNext(nodeRegiao);
                }

                node = getNext(node);
        }

}

void imprimirCaminho(Lista trajeto, char *path, char *corCaminho, int tipoPeso){

        FILE *svg = fopen(path, "a+");
        
        nodulo noduloVertice = getFirst(trajeto);
        nodulo aux = noduloVertice;

        Info comeco = getInfo(aux);
        ponto coordComeco = retornaVerticeCoord(comeco);

        fprintf(svg,"<circle fill-opacity=\"0.5\" cx=\"%lf\" cy=\"%lf\" r=\"9\" fill=\"black\" stroke=\"black\" stroke-width=\"1\" />\n", retornaPonto_X(coordComeco), retornaPonto_Y(coordComeco));
        fprintf(svg,"<text font-family=\"Arial\" x=\"%lf\" y=\"%lf\" stroke=\"white\" fill= \"white\" font-size=\"6\" text-anchor= \"middle\">I</text>\n", retornaPonto_X(coordComeco), retornaPonto_Y(coordComeco));
        
        while(noduloVertice!=NULL){

                aux = noduloVertice;
                noduloVertice = getNext(noduloVertice);

                if(noduloVertice==NULL){
                        break;
                }

                Info vertice1 = getInfo(aux);
                Info vertice2 = getInfo(noduloVertice);

                ponto coordV1 = retornaVerticeCoord(vertice1);
                ponto coordV2 = retornaVerticeCoord(vertice2);
                
                fprintf(svg,"\n");
                //caminho mais curto
                if(tipoPeso==1){ 
                        fprintf(svg,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"%s\"/>",retornaPonto_Y(coordV1) - 1,retornaPonto_Y(coordV2) - 1,retornaPonto_X(coordV1) - 1,retornaPonto_X(coordV2) - 1, corCaminho);
                }else{
                        fprintf(svg,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"%s\"/>",retornaPonto_Y(coordV1) + 1,retornaPonto_Y(coordV2) + 1,retornaPonto_X(coordV1) + 1,retornaPonto_X(coordV2) + 1, corCaminho);
                }

        }

        Info fim = getInfo(aux);
        ponto coordFim = retornaVerticeCoord(fim);

        fprintf(svg,"<circle fill-opacity=\"0.5\" cx=\"%lf\" cy=\"%lf\" r=\"9\" fill=\"black\" stroke=\"black\" stroke-width=\"1\" />\n", retornaPonto_X(coordFim), retornaPonto_Y(coordFim));
        fprintf(svg,"<text font-family=\"Arial\" x=\"%lf\" y=\"%lf\" stroke=\"white\" fill= \"white\" font-size=\"6\" text-anchor= \"middle\">F</text>\n", retornaPonto_X(coordFim), retornaPonto_Y(coordFim));

        fclose(svg);

}

void imprimirGrafo(Grafo grafo, char *pathSvg, char *cor){

        FILE *path = fopen(pathSvg, "a+");
        int n = numeroDeVertices(grafo);

        for(int i=0;i<n;i++){

                Info vertice1 = retornaVertice(grafo, i);
                ponto coordV1 = retornaVerticeCoord(vertice1);
                Lista arestas = retornaListaArestas(grafo, i);
                ponto coordV2;

                nodulo noduloAresta = getFirst(arestas);

                fprintf(path,"\n");

                fprintf(path,"<circle cx=\"%lf\" cy=\"%lf\" r=\"3\" fill=\"black\" stroke=\"black\" stroke-width=\"1\" />\n", retornaPonto_X(coordV1), retornaPonto_Y(coordV1));

                while(noduloAresta){
                        Info aresta = getInfo(noduloAresta);
                        int *posicaoV2 = getModulo(searchHash(retornaHashTableGrafo(grafo),retornaArestaVertFim(aresta)));
                        
                        Info vertice2 = retornaVertice(grafo, *posicaoV2);
                        ponto coordV2 = retornaVerticeCoord(vertice2);

                        fprintf(path,"<circle cx=\"%lf\" cy=\"%lf\" r=\"3\" fill=\"black\" stroke=\"black\" stroke-width=\"1\" />\n", retornaPonto_X(coordV2), retornaPonto_Y(coordV2));
                        fprintf(path,"<line stroke-linecap=\"null\" stroke-linejoin=\"null\" y1=\"%lf\" y2=\"%lf\" x1=\"%lf\" x2=\"%lf\" stroke-opacity=\"null\" stroke-width=\"1\" stroke=\"%s\"\n/>",retornaPonto_Y(coordV1),retornaPonto_Y(coordV2),retornaPonto_X(coordV1),retornaPonto_X(coordV2), cor);
                        noduloAresta = getNext(noduloAresta);
                }
        }

        fclose(path);
}

void imprimirQuadtree(QuadTree quadTree, char *pathSvg){

        FILE *path = fopen(pathSvg, "w");

        fprintf(path, "<svg>");
        imprimirQuadtree_aux(getNoQt_root(quadTree),path,"red");
        fprintf(path, "</svg>");

        fclose(path);
}

void inserePonto(Lista lista, nodulo node, double x, double y, char *cor){

        double h, Rx, Ry;

        Modulo ponto = montaCirculo("-1","1", 2, x, y, cor, cor);
        Modulo line;

        Info infoPonto = montaInfo("c","-1",ponto);

        Info info = getInfoQt(NULL,node);
        Modulo elemento = getModulo(info);

        insertAfterLast(lista, infoPonto);

        if(strcmp(retornaTipo(info),"r")==0){      

                Rx = retornaRet_X(elemento) + retornaRet_W(elemento)/2;
                Ry = retornaRet_Y(elemento) + retornaRet_H(elemento)/2; 

                line = montaRetangulo("-2","1",x,y,Rx,Ry,cor,cor);

        }

        else if(strcmp(retornaTipo(info),"c")==0){

                line = montaRetangulo("-2","1",x,y,retornaCirc_X(elemento),retornaCirc_Y(elemento),cor,cor);
        }

        Info infoLine = montaInfo("l","-2", line);
        insertAfterLast(lista, infoLine);

}


void imprimePathAnimacaoSvg(char *path, Lista trajeto, Grafo grafo, int tipoPeso, char *cor){

        FILE *svg = fopen(path, "a+");

        nodulo noduloVertice = getFirst(trajeto);
        Info vertice = getInfo(noduloVertice);
        ponto coordComeco = retornaVerticeCoord(vertice);

        fprintf(svg,"<circle fill-opacity=\"0.5\" cx=\"%lf\" cy=\"%lf\" r=\"9\" fill=\"black\" stroke=\"black\" stroke-width=\"1\" />\n", retornaPonto_X(coordComeco), retornaPonto_Y(coordComeco));
        fprintf(svg,"<text font-family=\"Arial\" x=\"%lf\" y=\"%lf\" stroke=\"white\" fill= \"white\" font-size=\"6\" text-anchor= \"middle\">I</text>\n", retornaPonto_X(coordComeco), retornaPonto_Y(coordComeco));

        fprintf(svg,"<path style=\"stroke:%s;stroke-width:1px;fill-opacity:0\" d=\"", cor); 

        if(tipoPeso==1){
                fprintf(svg,"M  %lf,%lf", retornaPonto_X(coordComeco)-2, retornaPonto_Y(coordComeco) - 2);
        }else{
                fprintf(svg,"M  %lf,%lf", retornaPonto_X(coordComeco), retornaPonto_Y(coordComeco));
        }

        noduloVertice = getNext(noduloVertice);

        while(noduloVertice!=NULL){

                vertice = getInfo(noduloVertice);
                ponto coordVertice = retornaVerticeCoord(vertice);

                if(tipoPeso==1){
                        fprintf(svg," L %lf,%lf", retornaPonto_X(coordVertice)-2, retornaPonto_Y(coordVertice) - 2);
                }else{
                        fprintf(svg," L %lf,%lf", retornaPonto_X(coordVertice), retornaPonto_Y(coordVertice));
                }
                
                noduloVertice = getNext(noduloVertice);

        }

        fprintf(svg,"\" id=\"path%d\"/>\n",idPath);

        nodulo noduloVerticeFim = getLast(trajeto);
        Info InfoVerticeFim = getInfo(noduloVerticeFim);
        ponto coordFim = retornaVerticeCoord(InfoVerticeFim);

        fprintf(svg,"<circle fill-opacity=\"0.5\" cx=\"%lf\" cy=\"%lf\" r=\"9\" fill=\"black\" stroke=\"black\" stroke-width=\"1\" />\n", retornaPonto_X(coordFim), retornaPonto_Y(coordFim));
        fprintf(svg,"<text font-family=\"Arial\" x=\"%lf\" y=\"%lf\" stroke=\"white\" fill= \"white\" font-size=\"6\" text-anchor= \"middle\">F</text>\n", retornaPonto_X(coordFim), retornaPonto_Y(coordFim));

        fprintf(svg,"<rect x=\"\" y=\"\" width=\"10\" height=\"10\" fill=\"%s\">\n",cor);
        fprintf(svg,"<animateMotion dur=\"20s\" repeatCount=\"indefinite\">\n");
        fprintf(svg,"<mpath xlink:href=\"#path%d\"/>\n",idPath);
        fprintf(svg,"</animateMotion>\n");
        fprintf(svg,"</rect>\n");

        fclose(svg);

        idPath++;
}
