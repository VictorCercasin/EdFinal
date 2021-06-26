#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leqry.h"
#include "ponto.h"
#include "pathment.h"
#include "sort.h"

char *arrumaString(char *str){
        str[strlen(str)-1]='\0';
}

double calculaAreaQuad(Modulo quadra){

        double area = retornaQuadra_W(quadra) * retornaQuadra_H(quadra);

        return area;
}

double calculaAreaCirc(Modulo circ){

        double area = 3.14 * (retornaCirc_Raio(circ) * retornaCirc_Raio(circ));

        return area;
}

double areaQuadra(char *path, Lista listQRY, QuadTree quadTree, double x, double y, double w, double h){

        Modulo objeto;

        FILE *txt = fopen(path,"a+");

        int check;
        double areaTotal=0,area;

        Lista list = nosDentroRetanguloQt(quadTree, x, y, x+w, y+h);
        nodulo node = getFirst(list);
        nodulo aux;

        while(node != NULL){

                objeto = getModulo(getInfo(node));
                area = calculaAreaQuad(objeto);
                areaTotal = area + areaTotal;

                double x = retornaQuadra_X(objeto) + retornaQuadra_W(objeto)/2;
                double y = retornaQuadra_Y(objeto) + retornaQuadra_H(objeto)/2;

                char areaString[50];
                sprintf(areaString,"%.2f",area);

                texto text = montaTexto("-7",x,y,"black","black", areaString,strlen(areaString)+2);
                Info info = montaInfo("t","-7",text);

                insertAfterLast(listQRY,info);

                retangulo line = montaRetangulo("-5","1",x,0,x,y,"black","black");
                Info infoLine = montaInfo("l","-5",line);

                insertAfterLast(listQRY, infoLine);                        
                fprintf(txt,"CEP = %s Área= %lf\n",retornaQuadra_Cep(objeto), area);

                aux = node;
                node = getNext(node);
                removeNode(aux,list);
        }

        fclose(txt);
        free(list);

        return areaTotal;
}

double areaCirculo(QuadTree quadTree, double x, double y, double w, double h){
        
        Modulo objeto;

        int check;
        double areaTotal=0;
        
        Lista list = nosDentroRetanguloQt(quadTree, x, y, x+w, y+h);
        nodulo node = getFirst(list);
        nodulo aux;

        while(node != NULL){

                
                objeto = getModulo(getInfo(node));
                areaTotal = calculaAreaCirc(objeto) + areaTotal;
                
                aux = node;
                node = getNext(node);
                removeNode(aux,list);
        }

        free(list);

        return areaTotal;
}

void mudaCorBorda(nodulo node, char *cstrk){

        Modulo objeto = getModulo(getInfo(node));
        alteraRet_Corb(objeto, cstrk);
}

double maior(double a, double b){
        if(a>b){
                return a;
        }else{
                return b;
        }
}

int procuraPostoRegiao(poligono poly, ponto pnt){

        int i,j;
        int pos=0, neg=0;
        double x,y,x1,y1,x2,y2,d;

        if(retornaPoligono_Tam(poly) < 3){
                return -1; // Erro
        }

        ponto *array = retornaArrayPontos(poly);

        for(i=0;i<retornaPoligono_Tam(poly);i++){

                if(retornaPonto_X(array[i]) == retornaPonto_X(pnt) && retornaPonto_Y(array[i]) == retornaPonto_Y(pnt)){
                        return 0; // Existe um posto na região                          
                }

                x1 = retornaPonto_X(array[i]);
                y1 = retornaPonto_Y(array[i]);

                j = i < (retornaPoligono_Tam(poly)-1)? i+1:0;

                x2 = retornaPonto_X(array[j]);
                y2 = retornaPonto_Y(array[j]);

                x = retornaPonto_X(pnt);
                y = retornaPonto_Y(pnt);

                d = (x-x1)*(y2-y1) - (y-y1)*(x2-x1);

                if(d>0){
                        pos++;
                }
                if(d<0){
                        neg++;
                }

                if(pos > 0 && neg >0){
                        return 1;
                }

        }

        return 0;

}

void removeVerticesPoly(poligono poly, QtNo verticeQt){
        
        if(verticeQt == NULL){
                return; // Não há vertices
        }
        
        ModuloVertice vertice = getModulo(getInfoQt(NULL,verticeQt));
        ponto pnt = retornaVerticeCoord(vertice);

        if(procuraPostoRegiao(poly,pnt)==0){
                desativarVertice(vertice);
        }

        removeVerticesPoly(poly, getNE(verticeQt));
        removeVerticesPoly(poly, getNW(verticeQt));
        removeVerticesPoly(poly, getSE(verticeQt));
        removeVerticesPoly(poly, getSW(verticeQt));

}

int verificaInteriorCirc(double x, double y, double r, Info info){

        Modulo objeto = getModulo(info);

        int check=0;

        if(strcmp(retornaTipo(info),"q")==0){
                
                double dx = maior(x - retornaQuadra_X(objeto), (retornaQuadra_X(objeto) + retornaQuadra_W(objeto)) - x);
                double dy = maior(y - retornaQuadra_Y(objeto), (retornaQuadra_Y(objeto) + retornaQuadra_H(objeto)) - y);

                return !(r * r >= (dx*dx + dy*dy));
        }

        if(strcmp(retornaTipo(info),"h")==0 || strcmp(retornaTipo(info),"rb")==0 || strcmp(retornaTipo(info),"s")==0){

                double dist = sqrt(pow(y-retornaCirc_Y(objeto), 2) + pow(x - retornaCirc_X(objeto),2 ));

                if(dist < r){
                        return 0;
                }
        }

        if(strcmp(retornaTipo(info),"morador")==0){

                ponto pnt = retornaMorador_Ponto(objeto);

                double dist = sqrt(pow(y-retornaPonto_Y(pnt), 2) + pow(x - retornaPonto_X(pnt),2 ));

                if(dist < r){
                        return 0;
                }
        }

        if(strcmp(retornaTipo(info),"ec")==0){

                ponto pnt = getEstab_Ponto(objeto);

                double dist = sqrt(pow(y-retornaPonto_Y(pnt), 2) + pow(x - retornaPonto_X(pnt),2 ));

                if(dist < r){
                        return 0;
                }
        }

        if(strcmp(retornaTipo(info),"cv")==0){

                double dist = 0;

                if(retornaCasaFace(objeto)=='S'){
                        dist = sqrt( pow(y-retornaCasa_Y(objeto), 2) + pow(x - retornaCasa_Xc(objeto),2 ));
                }else if(retornaCasaFace(objeto)=='N'){
                        dist = sqrt( pow(y-(retornaCasa_Y(objeto)+retornaCasa_H(objeto)), 2) + pow(x - retornaCasa_Xc(objeto),2 ));
                }else if(retornaCasaFace(objeto)=='L'){
                        dist = sqrt( pow(y-(retornaCasa_Yc(objeto)), 2) + pow(x - retornaCasa_X(objeto),2 ));
                }else if(retornaCasaFace(objeto)=='O'){
                        dist = sqrt( pow(y-(retornaCasa_Yc(objeto)), 2) + pow(x - (retornaCasa_X(objeto)+retornaCasa_W(objeto)),2 ));
                }

                if(dist < r){
                        return 0;
                }
        }
        
        if(strcmp(retornaTipo(info),"vertice")==0){

                ponto coordVertice = retornaVerticeCoord(objeto);

                double dist = sqrt(pow(y-retornaPonto_Y(coordVertice), 2) + pow(x - retornaPonto_X(coordVertice),2 ));

                if(dist < r){
                        return 0;
                }
        }

        return 1;
}

int verificaInteriorRet(double r_x1, double r_y1, double r_x2,  double r_y2, Info info){
        
        int check = 0;

        Modulo objeto = getModulo(info);
        double x1, x2, x3, x4;
        double y1, y2, y3, y4;

        if(strcmp(retornaTipo(info),"q")==0){

                x1 = retornaQuadra_X(objeto);
                x2 = retornaQuadra_X(objeto) + retornaQuadra_W(objeto);
                x3 = retornaQuadra_X(objeto);
                x4 = retornaQuadra_X(objeto) + retornaQuadra_W(objeto);

                y1 = retornaQuadra_Y(objeto);
                y2 = retornaQuadra_Y(objeto);
                y3 = retornaQuadra_Y(objeto) + retornaQuadra_H(objeto);
                y4 = retornaQuadra_Y(objeto) + retornaQuadra_H(objeto);

                if(x1 < r_x1 || x1 > r_x2 || y1 < r_y1 || y1 > r_y2){
                        check++;
                }

                if(x2 < r_x1 || x2 > r_x2 || y2 < r_y1 || y2 > r_y2){
                        check++;
                }

                if(x3 < r_x1 || x3 > r_x2 || y3 < r_y1 || y3 > r_y2){
                        check++;
                }

                if(x4 < r_x1 || x4 > r_x2 || y4 < r_y1 || y4 > r_y2){
                        check++;
                }
                
        }

        else if(strcmp(retornaTipo(info),"h")==0 || strcmp(retornaTipo(info),"s")==0 || strcmp(retornaTipo(info),"rb")==0){

                x1 = retornaCirc_X(objeto) - retornaCirc_Raio(objeto);
                x2 = retornaCirc_X(objeto) + retornaCirc_Raio(objeto);
                x3 = retornaCirc_X(objeto);
                x4 = retornaCirc_X(objeto);

                y1 = retornaCirc_Y(objeto);
                y2 = retornaCirc_Y(objeto);
                y3 = retornaCirc_Y(objeto) - retornaCirc_Raio(objeto);
                y4 = retornaCirc_Y(objeto) + retornaCirc_Raio(objeto);

                if(x1 < r_x1 || x1 > r_x2 || y1 < r_y1 || y1 > r_y2){
                        check++;
                }

                if(x2 < r_x1 || x2 > r_x2 || y2 < r_y1 || y2 > r_y2){
                        check++;
                }

                if(x3 < r_x1 || x3 > r_x2 || y3 < r_y1 || y3 > r_y2){
                        check++;
                }

                if(x4 < r_x1 || x4 > r_x2 || y4 < r_y1 || y4 > r_y2){
                        check++;
                }
        }

        else if(strcmp(retornaTipo(info),"ps")==0){
                x1 = retornaPonto_X(objeto);
                y1 = retornaPonto_Y(objeto);

                if(x1 < r_x1 || x1 > r_x2 || y1 < r_y1 || y1 > r_y2){
                        check++;
                }

                return check;
        }

        else if(strcmp(retornaTipo(info),"ec")==0){

                ponto pnt = getEstab_Ponto(objeto);

                x1 = retornaPonto_X(pnt);
                y1 = retornaPonto_Y(pnt);

                if(x1 < r_x1 || x1 > r_x2 || y1 < r_y1 || y1 > r_y2){
                        check++;
                }

                return check;
        }

        else if(strcmp(retornaTipo(info),"poly")==0){

                ponto *arrayPnt = retornaArrayPontos(objeto);

                double x1 = retornaPonto_X(arrayPnt[0]), x2 = retornaPonto_X(arrayPnt[0]); //menores
                double y1 = retornaPonto_Y(arrayPnt[0]), y2 = retornaPonto_Y(arrayPnt[0]); //maiores

                int tam = retornaPoligono_Tam(objeto);

                for(int i=0;i<tam;i++){
                        if(retornaPonto_X(arrayPnt[i]) < x1)
                                x1 = retornaPonto_X(arrayPnt[i]);
                        if(retornaPonto_X(arrayPnt[i]) > x2)
                                x2 = retornaPonto_X(arrayPnt[i]);
                        if(retornaPonto_Y(arrayPnt[i]) < y1)
                                y1 = retornaPonto_Y(arrayPnt[i]);
                        if(retornaPonto_Y(arrayPnt[i]) > y2)
                                y2 = retornaPonto_Y(arrayPnt[i]);  
                }


                if((x1 >= r_x1 && y1 >= r_y1 && x2 <= r_x2 || y2 <= r_y2)!=1){
                        check++;
                }

                return check;
        }

        return check;
}

int verificaInteriorPoly(poligono poly, QtNo posto){

        int check=1;

        if(posto == NULL){
                return 1; // Não há postos de saúde 
        }
        
        ponto pnt = getModulo(getInfoQt(NULL,posto));
        check = procuraPostoRegiao(poly,pnt);

        if(check!=0){
                check = verificaInteriorPoly(poly, getNE(posto));
        }

        if(check!=0){
                check = verificaInteriorPoly(poly, getNW(posto));
        }

        if(check!=0){
                check = verificaInteriorPoly(poly, getSE(posto));
        }

        if(check!=0){
                check = verificaInteriorPoly(poly, getSW(posto));
        }

        return check; 
}

void testeInterior(char *pathTXT, QuadTree circulos, QuadTree retangulos,Lista lista, char *id, double x, double y){

        nodulo node;

        Info info;
        Modulo elemento;

        double mx, my, Mx, My;
        char cor[30];

        if(circulos != NULL){
                node = getNoQt_byId(circulos, id);
        }
        if(retangulos != NULL && node == NULL){
                node = getNoQt_byId(retangulos, id);
        }

        if(node == NULL){
                return;
        }

        info = getInfoQt(NULL,node);
        elemento = getModulo(info);
        
        if(strcmp(retornaTipo(info),"r")==0){         
                if(x < retornaRet_X(elemento) || x > retornaRet_X(elemento) + retornaRet_W(elemento) || y < retornaRet_Y(elemento) || y > retornaRet_Y(elemento) + retornaRet_H(elemento)){
                        strcpy(cor,"magenta");
                }
                else{
                        strcpy(cor,"blue");
                }
        }

        else if(strcmp(retornaTipo(info),"c")==0){

                mx = retornaCirc_X(elemento) - retornaCirc_Raio(elemento);
                my = retornaCirc_Y(elemento) - retornaCirc_Raio(elemento);

                Mx = retornaCirc_X(elemento) + retornaCirc_Raio(elemento);
                My = retornaCirc_Y(elemento) + retornaCirc_Raio(elemento);

                if(x<mx || x>Mx || y<my|| y>My){
                        strcpy(cor,"magenta");
                }
                else{
                        strcpy(cor,"blue");
                }
        }

        if(strcmp(cor,"blue")==0){
                iTxt(pathTXT, node, "INTERNO");
        }

        else if(strcmp(cor,"magenta")==0){
                iTxt(pathTXT, node, "NAO INTERNO");
        }

        inserePonto(lista, node, x, y, cor);
        completarTxt(pathTXT);

}

void carregarLinhaVertical(Lista listagem, Info info, char *idRegistrador){

        Modulo objeto = getModulo(info);

        double y2 = 0, x1, x2, y1;

        if(strcmp(retornaTipo(info),"c") == 0 || strcmp(retornaTipo(info),"rb") ==0 || strcmp(retornaTipo(info),"s")==0 || strcmp(retornaTipo(info), "h")==0){
                y1 = retornaCirc_Y(objeto);
                x1 = retornaCirc_X(objeto);
                x2 = x1;
        }

        else if(strcmp(retornaTipo(info),"r")==0){
                y1 = retornaRet_Y(objeto) + retornaRet_H(objeto)/2;
                x1 = retornaRet_X(objeto) + retornaRet_W(objeto)/2;
                x2 = x1;
        }
         
        else if(strcmp(retornaTipo(info), "q")==0){
                y1 = retornaQuadra_Y(objeto) + retornaQuadra_H(objeto)/2;
                x1 = retornaQuadra_X(objeto) + retornaQuadra_W(objeto)/2;
                x2 = x1;
        }

        else if(strcmp(retornaTipo(info),"morador")==0){
                ponto p = retornaMorador_Ponto(objeto);
                y1 = retornaPonto_Y(p);
                x1 = retornaPonto_X(p);
                x2 = x1;
        }

        else{
                return;
        }

        retangulo line = montaRetangulo("-5","1",x2,y2,x1,y1,"black","black");
        Info infoLine = montaInfo("l","-5",line);

        insertAfterLast(listagem, infoLine);

        if(idRegistrador!=NULL){
                texto text = montaTexto("-6",x1+1,y2+1,"black","black", idRegistrador, strlen(idRegistrador)+2);
                Info infoText = montaInfo("t","-6",text);

                insertAfterLast(listagem, infoText);
        }

        else if(strcmp(retornaTipo(info),"morador")==0){

                Pessoa p = retornaMorador_Pessoa(objeto);

                texto text = montaTexto("-6",x1+1,y2+1,"black","black", retornaPos(info), strlen(retornaPos(info))+2);
                Info infoText = montaInfo("t","-6",text);

                insertAfterLast(listagem, infoText);

                texto text2 = montaTexto("-6",x1+1,y2+20,"black","black", retornaPessoa_Nome(p), strlen(retornaPessoa_Nome(p))+2);
                Info infoText2 = montaInfo("t","-6",text2);

                insertAfterLast(listagem, infoText2);

                texto text4 = montaTexto("-6",x1+1,y2+40,"black","black", retornaMorador_Cep(objeto) , strlen(retornaMorador_Cep(objeto))+2);
                Info infoText4 = montaInfo("t","-6",text4);

                insertAfterLast(listagem, infoText4);
        }else{
                texto text = montaTexto("-6",x1+1,y2+1,"black","black", retornaPos(info), strlen(retornaPos(info))+2);
                Info infoText = montaInfo("t","-6",text);

                insertAfterLast(listagem, infoText);
        }

}

char *determinaCategoria(double incidencia){

        if(incidencia < 0.1){
                return "00FFFF";
        }
        else if(incidencia < 5){
                return "008080";
        }
        else if(incidencia < 10){
                return "FFFF00";
        }
        else if(incidencia < 20){
                return "FF0000";
        }
        else{
                return "800080";
        }

}

regiao encontrarRegiao(Info infoPoly, QtNo regiao_No, regiao reg){

        if(reg != NULL || regiao_No == NULL){
                return reg;
        }

        Info info = getInfoQt(NULL,regiao_No);
        int check;

        if(info != NULL){

                regiao regiao_Objeto = getModulo(info);

                double x = retornaReg_X(regiao_Objeto);
                double y = retornaReg_Y(regiao_Objeto);
                double w = retornaReg_W(regiao_Objeto);
                double h = retornaReg_H(regiao_Objeto);

                check = verificaInteriorRet(x, y, x+w, y+h, infoPoly);

                if(check==0){
                       reg = regiao_Objeto;
                }
        }

        if(reg==NULL){
                reg =   encontrarRegiao(infoPoly, getNE(regiao_No), reg);
        }

        if(reg==NULL){
                reg =  encontrarRegiao(infoPoly, getNW(regiao_No), reg);
        }

        if(reg==NULL){
                reg =  encontrarRegiao(infoPoly, getSE(regiao_No), reg);
        }
        
        if(reg==NULL){
                reg =  encontrarRegiao(infoPoly, getSW(regiao_No), reg);
        }

        return reg;

}

int sobre2Circ(Modulo forma1, Modulo forma2){

        double xR,yR,xr,yr,xR2,yR2,xr2,yr2;

        xR = retornaCirc_X(forma1) + retornaCirc_Raio(forma1);
        yR = retornaCirc_Y(forma1) + retornaCirc_Raio(forma1);

        xr = retornaCirc_X(forma1) - retornaCirc_Raio(forma1);
        yr = retornaCirc_Y(forma1) - retornaCirc_Raio(forma1);

        xR2 = retornaCirc_X(forma2) + retornaCirc_Raio(forma2);
        yR2 = retornaCirc_Y(forma2) + retornaCirc_Raio(forma2);

        xr2 = retornaCirc_X(forma2) - retornaCirc_Raio(forma2);
        yr2 = retornaCirc_Y(forma2) - retornaCirc_Raio(forma2);

        if(xR2 < xr || xr2 > xR || yR2 < yr || yr2 > yR){
                return 1;
        }
        else{
                return 0;
        } 

}

int sobreCircRet(Modulo circ, Modulo ret){

        double xR,yR,xr,yr,xw,yh;
        

        xR = retornaCirc_X(circ) + retornaCirc_Raio(circ);
        yR = retornaCirc_Y(circ) + retornaCirc_Raio(circ);

        xr = retornaCirc_X(circ) - retornaCirc_Raio(circ); 
        yr = retornaCirc_Y(circ) - retornaCirc_Raio(circ);

        xw = retornaRet_X(ret) + retornaRet_W(ret);
        yh = retornaRet_Y(ret) + retornaRet_H(ret);

        if(retornaRet_X(ret) > xR || retornaRet_Y(ret) > yR || xw < xr || yh < yr){
                return 1;
        }

        else{
                return 0;
        }

}

int sobre2Ret(Modulo forma1, Modulo forma2){
        
        double xw,yh,xw2,yh2;

        xw = retornaRet_X(forma1) + retornaRet_W(forma1);
        yh = retornaRet_Y(forma1) + retornaRet_H(forma1);

        xw2 = retornaRet_X(forma2) + retornaRet_W(forma2);
        yh2 = retornaRet_Y(forma2) + retornaRet_H(forma2);

        if(xw < retornaRet_X(forma2) || yh < retornaRet_Y(forma2) || retornaRet_X(forma1) > xw2 || retornaRet_Y(forma1) > yh2){
                return 1;
        }
        else{
                return 0;
        }
        
}

int analisaSobreposicao(nodulo node1,nodulo node2){

        Info info = getInfoQt(NULL,node1); 
        Info info2 = getInfoQt(NULL,node2);

        Modulo forma1 = getModulo(info);
        Modulo forma2 = getModulo(info2);

        if(strcmp(retornaTipo(info),"c")==0){          

                if(strcmp(retornaTipo(info2),"r")==0){   
                        return sobreCircRet(forma1,forma2);
                }
                else if(strcmp(retornaTipo(info2),"c")==0){
                        return sobre2Circ(forma1,forma2);
                }
        }
        else if(strcmp(retornaTipo(info),"r")==0){

                if(strcmp(retornaTipo(info2),"c")==0){
                        return sobreCircRet(forma2,forma1);
                }
                else if(strcmp(retornaTipo(info2),"r")==0){
                        return sobre2Ret(forma1,forma2);
                }

        }
}

double min_xy(nodulo node1, nodulo node2, int i){

        Info info = getInfoQt(NULL,node1); 
        Info info2 = getInfoQt(NULL,node2);

        Modulo forma1 = getModulo(info); 
        Modulo forma2 = getModulo(info2);

        double mx, my, x, y;
        
        if(strcmp(retornaTipo(info),"c")==0){   
                mx = retornaCirc_X(forma1) - retornaCirc_Raio(forma1);
                my = retornaCirc_Y(forma1) - retornaCirc_Raio(forma1);
        }

        else if(strcmp(retornaTipo(info),"r")==0){
                mx = retornaRet_X(forma1);
                my = retornaRet_Y(forma1);
        }

        if(strcmp(retornaTipo(info2),"c")==0){
                x = retornaCirc_X(forma2) - retornaCirc_Raio(forma2);
                y = retornaCirc_Y(forma2) - retornaCirc_Raio(forma2);
        }

        else if(strcmp(retornaTipo(info2),"r")==0){
                x = retornaRet_X(forma2);
                y = retornaRet_Y(forma2);
        }

        if(mx > x){
                mx = x;
        }

        if(my > y){
                my = y;
        }

        if(i==0){
                return mx;
        }

        else if (i==1){
                return my;
        }

}

double max_xy(nodulo node1, nodulo node2, int i){

        Info info = getInfoQt(NULL,node1);
        Info info2 = getInfoQt(NULL,node2);

        Modulo forma1 = getModulo(info);
        Modulo forma2 = getModulo(info2);

        double Mx, My, x, y;
        
        if(strcmp(retornaTipo(info),"c")==0){
                Mx = retornaCirc_X(forma1) + retornaCirc_Raio(forma1);
                My = retornaCirc_Y(forma1) + retornaCirc_Raio(forma1);
        }

        if(strcmp(retornaTipo(info),"r")==0){
                Mx = retornaRet_X(forma1) + retornaRet_W(forma1);
                My = retornaRet_Y(forma1) + retornaRet_H(forma1);
        }

        if(strcmp(retornaTipo(info2),"c")==0){
                x = retornaCirc_X(forma2) + retornaCirc_Raio(forma2);
                y = retornaCirc_Y(forma2) + retornaCirc_Raio(forma2);
        }

        if(strcmp(retornaTipo(info2),"r")==0){
                x = retornaRet_X(forma2) + retornaRet_W(forma2);
                y = retornaRet_Y(forma2) + retornaRet_H(forma2);
        }

        if(Mx < x){
                Mx = x;
        }

        if(My < y){
                My = y;
        }

        if(i==0){
                return Mx;
        }
        else if(i==1){
                return My;
        }

}

void montaSobreposicao(char *pathTXT, Lista listQRY, QuadTree circulos, QuadTree retangulos, char *i, char *j){

        double  x , y, w, h , mx, my, Mx, My;

        nodulo node1;
        nodulo node2;

        Modulo forma1;
        Modulo forma2;

        node1 = getNoQt_byId(circulos, i);
        node2 = getNoQt_byId(circulos, j);

        if(node1 == NULL){
                node1 = getNoQt_byId(retangulos, i);
        }

        if(node2 == NULL){
                node2 = getNoQt_byId(retangulos, j);
        }

        Info info = getInfoQt(NULL,node1); 
        Info info2 = getInfoQt(NULL,node2);

        mx = min_xy(node1,node2,0); // menor x dentre as 2 figuras
        my = min_xy(node1,node2,1); // menor y dentre as 2 figuras

        Mx = max_xy(node1,node2,0); // Maior X dentre as 2 figuras
        My = max_xy(node1,node2,1); // Maior Y dentre as 2 figuras

        w = Mx - mx + 1; // Largura do quadrado de sobreposição
        h =  My - my + 1; // Altura do quadrado de sobreposição

        x = mx - 1;
        y = my - 1;

        if(analisaSobreposicao(node1,node2) == 0){ //forma1 e forma2
                carregaRetLine(listQRY,x,y,h,w); 
                oTxt(pathTXT,node1,node2,"SIM");
        }
        else{
                carregaRetTracado(listQRY,x,y,h,w);
                oTxt(pathTXT,node1,node2,"NAO");
        }
                   
}

void mudaCor(char *pathTXT, QuadTree circulos, QuadTree retangulos, QuadTree textos, char *id, char *corb, char *corp){

        nodulo node;

        node = getNoQt_byId(circulos, id);
        
        if(node == NULL){
                node = getNoQt_byId(retangulos, id);
        }

        if(node == NULL){
                node = getNoQt_byId(textos, id);
        }      

        if(node == NULL){
                return;
        }

        Info info = getInfoQt(NULL,node);
        Modulo elemento = getModulo(info);
 
        if(strcmp(retornaTipo(info),"c")==0){

                alteraCirc_Corb(elemento,corb);
                alteraCirc_Corp(elemento,corp);
        }
        else if(strcmp(retornaTipo(info),"r")==0){
                alteraRet_Corb(elemento,corb);
                alteraRet_Corp(elemento,corp);
        }else{
                alteraTexto_Corb(elemento,corb);
                alteraTexto_Corp(elemento,corp);
        }

        pntTxt(pathTXT, info);

}

void imprimeCATAC(Lista list, char *pathTXT, Lista listQRY, HashTable codtXdesc){

        nodulo node = getFirst(list);

        while(node!=NULL){

                Info info = getInfo(node);

                delfTxt(pathTXT, info);

                node = getNext(node);
        }
}

void remocaoCATAC_Qt(Lista list, QuadTree qt, HashTable cepXquadra){

        nodulo node = getFirst(list);

        while(node!=NULL){

                Info info = getInfo(node);
                char *id = retornaPos(info);

                if(strcmp(retornaTipo(info),"q")==0){
                        removeHT(cepXquadra, retornaQuadra_Cep(getModulo(info)));
                }

                QtNo nodeQt = getNoQt_byId(qt, id);
                removeQt(qt, nodeQt);

                node = getNext(node);
        }
}

void criarTrajeto(Grafo grafo, Lista trajeto, int *anterior, int posicao){

    if(anterior[posicao]==-1){
        return;
    }

    criarTrajeto(grafo, trajeto, anterior, anterior[posicao]);
    insertAfterLast(trajeto, retornaVertice(grafo, posicao));
}

void imprimirTrajetoTxt(Lista trajeto, char *path, int tipoPeso){
        
        FILE *txt = fopen(path, "a+");

        if(tipoPeso == 1){
                fprintf(txt, "\n*Trajeto mais rápido*\n");
        }else{
                fprintf(txt, "\n*Trajeto mais curto*\n");
        }

        char *orientacaoAnt = "nenhuma";
        char *orientacao;

        nodulo noduloVertice = getFirst(trajeto);

        while(noduloVertice!=NULL){

                nodulo aux = noduloVertice;
                noduloVertice = getNext(noduloVertice);

                if(noduloVertice==NULL){
                        break;
                }

                Info vertice1 = getInfo(aux);
                Info vertice2 = getInfo(noduloVertice);

                Info aresta = encontrarAresta(vertice1, vertice2);

                ponto coordV1 = retornaVerticeCoord(vertice1);
                ponto coordV2 = retornaVerticeCoord(vertice2);

                if(retornaPonto_Y(coordV1) < retornaPonto_Y(coordV2))
                        orientacao = "norte";
                
                else if(retornaPonto_Y(coordV1) > retornaPonto_Y(coordV2))
                        orientacao = "sul";

                else if(retornaPonto_X(coordV1) > retornaPonto_X(coordV2))
                        orientacao = "leste";
                
                else if(retornaPonto_X(coordV1) < retornaPonto_X(coordV2))
                        orientacao = "oeste";

                if(orientacaoAnt == "nenhuma"){
                        fprintf(txt, "Siga na direção %s na rua %s", orientacao, retornaNomeRua(aresta));
                }  

                else if(strcmp(orientacao,orientacaoAnt)!=0){
                        fprintf(txt, " até o cruzamento com a rua %s. ", retornaNomeRua(aresta));
                        fprintf(txt, "Siga na direção %s na rua %s", orientacao, retornaNomeRua(aresta));
                }      

                orientacaoAnt = orientacao;
        }

        if(strcmp(orientacaoAnt, "anterior")==0){
                fprintf(txt, "Nao foi encontrado um trajeto entre os dois vertices.");
        }else{
                fprintf(txt, ". Você chegou ao destino final.\n\n");
        }

        fclose(txt);
}

int verticeMaisProximo(Grafo grafo, ponto coord){

        Info *vertices = retornaVertices(grafo);
        int n = numeroDeVertices(grafo);

        double dist = 33000000.0;
        int menorIndice;

        for(int i=0;i<n;i++){

                //se estiver inativo/deletado, ele nao considera o vertice
                if(verticeAtivo(retornaVertice(grafo,i)) == 0){
                        continue;
                }

                double distancia = distSq(coord, retornaVerticeCoord(vertices[i]));

                if(distancia<dist){
                        dist = distancia;
                        menorIndice = i;
                }
        }
      
        return menorIndice;
}

void remocaoCATAC_Vertices(Lista lVertices, Grafo grafo, char *pathTXT){
        
        FILE *txt = fopen(pathTXT, "a+");
        nodulo node = getFirst(lVertices);

        while(node){
                Info infoVertice = getInfo(node);
                ModuloVertice vertice = getModulo(infoVertice);

                fprintf(txt, "\nVertice de ID: %s e Coordenadas X: %lf e Y: %lf removido", retornaVerticeId(vertice), retornaPonto_X(retornaVerticeCoord(vertice)), retornaPonto_Y(retornaVerticeCoord(vertice)));

                desativarVertice(vertice);
                node = getNext(node);
        }

        fclose(txt);
}

void fazCATAC(char *pathTXT, double x, double y, double r, Grafo grafo, Lista moradores, Lista estabComerc, QuadTree quadras, QuadTree hidrantes, QuadTree torresCel, QuadTree semaforos, Lista listQRY, HashTable codtXdesc, HashTable cepXquadra, HashTable cpfXpessoa){

        Lista lQuadras = nosDentroCirculoQt(quadras, x, y, r);
        Lista lHidrantes = nosDentroCirculoQt(hidrantes, x, y, r);

        Lista lTorresCel = nosDentroCirculoQt(torresCel, x, y, r);
        Lista lSemaforos = nosDentroCirculoQt(semaforos, x, y, r);

        Lista lVertices = nosDentroCirculoQt(retornaVerticesQtGrafo(grafo), x, y, r);

        imprimeCATAC(lQuadras, pathTXT, listQRY, codtXdesc);
        imprimeCATAC(lHidrantes, pathTXT, listQRY, codtXdesc);
        imprimeCATAC(lTorresCel, pathTXT, listQRY, codtXdesc);
        imprimeCATAC(lSemaforos, pathTXT, listQRY, codtXdesc);

        nodulo node = getFirst(moradores);
        int check;

        carregaCircCalac(listQRY, x, y, r, "#CCFF00,", "#6C6753");

        while(node != NULL){

                Info info = getInfo(node);

                check = verificaInteriorCirc(x, y, r, info);

                if(check==0){
                        moradorTxt(pathTXT, getModulo(info));

                        nodulo aux = node;
                        node = getNext(node);
                        Morador m = getModulo(info);

                        Info infoQuadra = removeHT(cepXquadra,retornaMorador_Cep(m));
                        
                        removerElemento(moradores,aux);

                }else{
                       node = getNext(node); 
                }

        }

        node = getFirst(estabComerc);

        while(node != NULL){

                Info info = getInfo(node);
                check = verificaInteriorCirc(x, y, r, info);

                if(check==0){

                        Info infoDesc = searchHash(codtXdesc, getEstab_Codt(getModulo(info)));

                        if(infoDesc!=NULL){
                                estabTxt(pathTXT, getModulo(info), getString(getModulo(infoDesc)));
                                removeHT(codtXdesc,getEstab_Codt(getModulo(info)));
                                removeInfo(infoDesc);
                        }

                        nodulo aux = node;
                        node = getNext(node);

                        removerElemento(estabComerc,aux);

                }else{
                       node = getNext(node); 
                }

        }

        remocaoCATAC_Qt(lQuadras, quadras, cepXquadra);
        remocaoCATAC_Qt(lHidrantes, hidrantes, cepXquadra);
        remocaoCATAC_Qt(lTorresCel, torresCel, cepXquadra);
        remocaoCATAC_Qt(lSemaforos, semaforos, cepXquadra);
        
        remocaoCATAC_Vertices(lVertices, grafo, pathTXT);

        limparLista_aux(lQuadras);
        limparLista_aux(lHidrantes);
        limparLista_aux(lTorresCel);
        limparLista_aux(lSemaforos);

}

void fazEPLG(char *pathTXT, char *codt, double x, double y, double w, double h, Lista estabComerc, HashTable codtXdesc, Lista listQRY){

        nodulo node = getFirst(estabComerc);
        int check;

        while(node != NULL){

                Info info = getInfo(node);
                estabComercial ec = getModulo(info);
                

                if(strcmp(getEstab_Codt(ec),codt)==0 || strcmp(getEstab_Codt(ec),"*")==0){
                        
                        ponto pnt = getEstab_Ponto(ec);

                        Modulo pontoEc = montaPonto(retornaPonto_X(pnt), retornaPonto_Y(pnt));
                        Info iPontoEc = montaInfo("pontoEc","null",pontoEc);

                        insertAfterLast(listQRY, iPontoEc);

                        check = verificaInteriorRet(x, y, x+w, h+y, info);

                        if(check == 0){

                                Info infoDesc = searchHash(codtXdesc, getEstab_Codt(ec));
                                estabTxt(pathTXT, ec, getString(getModulo(infoDesc)));

                                ponto pnt = getEstab_Ponto(ec);

                                Modulo pontoEc = montaPonto(retornaPonto_X(pnt), retornaPonto_Y(pnt));
                                Info iPontoEc = montaInfo("pontoEc","null",pontoEc);

                                insertAfterLast(listQRY, iPontoEc);
                        }
                }

                node = getNext(node);
        }

}

void fazMUD(char *pathTXT, char *cpf, char *cep, char *face, int num, char *compl, HashTable cpfXcep, HashTable cpfXpessoa, HashTable cepXquadra, Lista moradores, Lista listQRY){
        
        
        nodulo node = getFirst(moradores);

        Info infoCep = searchHash(cpfXcep, cpf);
        if(infoCep == NULL){
                return;
        }
        String strCep = getModulo(infoCep);
        
        Info infoPessoa = searchHash(cpfXpessoa,cpf);
        if(infoPessoa==NULL){
                return;
        }
        Pessoa p = getModulo(infoPessoa);

        while(node!=NULL){

                Info infoMorador = getInfo(node);
                Morador m = getModulo(infoMorador);
                char *cepAtual = retornaMorador_Cep(m);
                Pessoa pLista = retornaMorador_Pessoa(m);

                if(p == pLista){

                        mudancaTxt(pathTXT, m, cep, face[0], num, compl);
                        Info infoQuadra = searchHash(cepXquadra, cep);

                        if(infoQuadra == NULL){
                                return;
                        }

                        ponto pnt = retornaMorador_Ponto(m);

                        double x1 = retornaPonto_X(pnt);
                        double y1 = retornaPonto_Y(pnt);

                        carregaPonto(listQRY,x1,y1,"red");

                        alteraMorador_Endereco(getModulo(infoMorador), getModulo(infoQuadra), face[0], num, compl);
                        pnt = retornaMorador_Ponto(m);
                        carregaPonto(listQRY,retornaPonto_X(pnt),retornaPonto_Y(pnt),"blue");
                        carregaLinha(listQRY, x1, y1,retornaPonto_X(pnt), retornaPonto_Y(pnt),"red");
                
                        alteraString(strCep,cep);
                }
                
                node = getNext(node);
        }
}

void fazDE(char *pathTXT, char *cnpj , estabComercial estabComerc, HashTable codtXdesc){

        nodulo node = getFirst(estabComerc);

        while(node!=NULL){

                Info infoEstab = getInfo(node);
                estabComercial ec = getModulo(infoEstab);
                Pessoa p = getEstab_Pessoa(ec);

                if(strcmp(cnpj, getEstab_Cnpj(ec))==0){

                        Info infoDesc = searchHash(codtXdesc, getEstab_Codt(ec));

                        if(infoDesc==NULL){
                                return;
                        }

                        estabTxt(pathTXT, ec, getString(getModulo(infoDesc)));
                }

                node = getNext(node);
        }

}

void fazDM(char *pathTXT, char *cpf , Lista moradores, HashTable cpfXpessoa, Lista listQRY){

        nodulo node = getFirst(moradores);

        Info infoPessoa = searchHash(cpfXpessoa,cpf);
        
        if(infoPessoa == NULL){
                return;
        }

        Pessoa p = getModulo(infoPessoa);

        while(node!=NULL){
                Info infoMorador = getInfo(node);
                Morador m = getModulo(infoMorador);

                if(retornaMorador_Pessoa(m) == p){
                        moradorTxt(pathTXT, m);
                        carregarLinhaVertical(listQRY, infoMorador, NULL);
                }

                node = getNext(node);
        }

}

void fazM(char *pathTXT, char *cep, Lista moradores, HashTable cepXquadra){

        nodulo node = getFirst(moradores);
        
        Info infoQuadra = searchHash(cepXquadra,cep);
        if(infoQuadra == NULL){
                FILE *arq = fopen(pathTXT,"a+");
                fprintf(arq,"Quadra inexistente\n");
                fclose(arq);
                return;
        }

        while(node != NULL){
                Info infoMorador = getInfo(node);
                if(strcmp(cep,retornaMorador_Cep(getModulo(infoMorador)))==0){
                        moradorTxt(pathTXT,getModulo(infoMorador));
                }

                node = getNext(node);
        }
}

void fazSOC_aux(Grafo grafo, char *path, ponto posto, Lista listQRY, ponto referencial){

        int posicaoVerticeReferencial = verticeMaisProximo(grafo, referencial);
        Info verticeReferencial = retornaVertice(grafo, posicaoVerticeReferencial);
        ponto coordVetRef = retornaVerticeCoord(verticeReferencial);

        carregaLinha(listQRY, retornaPonto_X(coordVetRef), retornaPonto_Y(coordVetRef), retornaPonto_X(referencial), retornaPonto_Y(referencial), "green");

        int posicaoVertice = verticeMaisProximo(grafo, posto);
        Info vertice = retornaVertice(grafo, posicaoVertice);

        int *anterior = malloc(numeroDeVertices(grafo) * sizeof(int));
        double *distancia = dijkstra(grafo, posicaoVerticeReferencial, 2, anterior);

        if(anterior[posicaoVertice] == -1){
                free(anterior);
                free(distancia);
                return; //nao achou um caminho
        }

        Lista trajeto = criarLista();
        insertAfterLast(trajeto, verticeReferencial);
        criarTrajeto(grafo, trajeto, anterior, posicaoVertice);
        imprimirTrajetoTxt(trajeto, path, 2);

        nodulo noduloVertice = getFirst(trajeto);
        nodulo aux=NULL;

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
                
                carregaLinha(listQRY, retornaPonto_X(coordV1), retornaPonto_Y(coordV1), retornaPonto_X(coordV2), retornaPonto_Y(coordV2), "green");                        
        }

        Info verticeFinal = getInfo(aux);
        ponto coordFinal = retornaVerticeCoord(verticeFinal);
        carregaLinha(listQRY, retornaPonto_X(posto), retornaPonto_Y(posto), retornaPonto_X(coordFinal), retornaPonto_Y(coordFinal), "green");

        limparLista_aux(trajeto);
        free(anterior);
        free(distancia);
        
}

void fazSOC(Grafo grafo, char *path, QuadTree postos,Lista casas,QuadTree quadras, Lista listQRY, char info[][50]){

        int tam = getQt_ObjAmount(postos);

        int i=0;

        nodulo nodeQuadra = getNoQt_byId(quadras, info[2]);

        if(nodeQuadra == NULL){
                return;
        }

        Quadra quad = getModulo(getInfoQt(quadras,nodeQuadra));
                
        ponto ref = pontoCentral_Endereco(quad,info[3],transfStringInt(info[4]));

        if(ref==NULL){
                return;
        }

        ponto *array = criaArrayPontos(tam);

        int ret = quadTreeToArray(getNoQt_root(postos), array, tam-1);

        retangulo quadrado_azul = montaRetangulo("quad_azul","1",5,5,retornaPonto_X(ref),retornaPonto_Y(ref),"white","blue");
        Info info_quadrado = montaInfo("r","null", quadrado_azul);
        insertAfterLast(casas,info_quadrado);

        int k = transfStringInt(info[1]);
        int tamanhoPrimeiros;
        
        ponto *primeiros = shellSort(array,tam, k, ref,&tamanhoPrimeiros);

        for(i=0;i<tamanhoPrimeiros;i++){
                
                retangulo linha_tracejada = montaRetangulo("linha_tracejada","1",retornaPonto_X(ref) +2.5,retornaPonto_Y(ref)+ 2.5,retornaPonto_X(primeiros[i]), retornaPonto_Y(primeiros[i]),"red","red");
                pontoTxt(path,primeiros[i]);
                fazSOC_aux(grafo, path, primeiros[i], listQRY, ref);
                Info infoLine = montaInfo("lt","linha_tracejada",linha_tracejada);
                insertAfterLast(listQRY, infoLine);     
        }

        //fazSOC_aux(grafo, path, primeiros, listQRY, ref, tamanhoPrimeiros);

        removePonto(ref);

        for(i=0;i<tam;i++){
                free(array[i]);
        }
        free(array);
        
        if(tamanhoPrimeiros != tam){

                for(int i=0; i<tamanhoPrimeiros; i++){
                        free(primeiros[i]);
                }

                free(primeiros);
        }

}

void fazCI(char *path, Lista casas, QuadTree regioes, QuadTree postos, Lista poligonos,Lista listQRY, char info[][50]){

        double circulo_x = transfStringDouble(info[1]), circulo_y = transfStringDouble(info[2]), circulo_raio = transfStringDouble(info[3]);

        circulo circ = montaCirculo("circ-regiao","2",circulo_raio,circulo_x,circulo_y,"green","none");
        Info info_circ = montaInfo("c","null",circ);
        insertAfterLast(listQRY,info_circ);
        
        int numCasos=0, numPontos=0;
        char categoriaIncid;

        nodulo nodeCasa = getFirst(casas);
        casa c;
        Info info_atual;

        Lista pontos = criarLista();

        
        while(nodeCasa!=NULL){
                Info informacao = getInfo(nodeCasa);
                c = getModulo(informacao);
                int check = verificaInteriorCirc(circulo_x, circulo_y, circulo_raio, informacao);
                
                if(check == 0){
                        numCasos = numCasos + retornaCasa_N(c); // Vai somando o numero de casos
                        pntTxt(path, getInfo(nodeCasa));
                        insertAfterLast(pontos, informacao);
                        numPontos++; // Tamanho do vetor final de casas dentro do poligono
                }
                
                nodeCasa = getNext(nodeCasa);
        }

        if(numPontos<3){
                limparLista_aux(pontos);
                return;
        }

        nodulo nodePonto = getFirst(pontos);
        
        Info *array = (Info*) malloc(sizeof(Info)*numPontos);
        int i=0;      

        //Cria o vetor de pontos que será inserido na tad do poligono

        while(nodePonto!=NULL){
                array[i] = getInfo(nodePonto);
                i++;
                nodePonto = getNext(nodePonto);
        }

        //poligono pol = envoltoriaConvexa(array, numPontos);

        Lista raiz = envoltoriaConvexa(array, numPontos);

        int tam = listSize(raiz);
        i = 0;
        
        ponto *arrayFinal = criaArrayPontos(tam);

        nodulo node = getLast(raiz);
        
	while (node != NULL) 
	{ 
                Info info = getInfo(node);
		ponto p = retornaInfoCoord(info); 

                double x = retornaPonto_X(p);
                double y = retornaPonto_Y(p);
                arrayFinal[i] = montaPonto(x,y);
                i++;

		removeLast(raiz);
                node = getLast(raiz);
	} 

        poligono pol = montaPoligono(arrayFinal,tam);

        Info infoPol = montaInfo("poly","null",pol);
        insertAfterLast(poligonos, infoPol);
        
        long double area = areaPoligono(pol);
        int check = verificaInteriorPoly(pol,getNoQt_root(postos));

        if(check == 1){
                ponto novoPosto = encontrarCentroide(pol,area);
                Info info_novoPosto = montaInfo("ps","null", novoPosto);
                ponto p = novoPosto;
                insereQt(postos, p, info_novoPosto);
        }

        area = area/1000000;

        regiao reg = encontrarRegiao(infoPol,getNoQt_root(regioes),NULL);
        int numHab = area * retornaReg_D(reg);
        double incidencia = ((double)numCasos/numHab)*100000;

        addCor(pol,determinaCategoria(incidencia));

        comandoCiTxt(path,area,numCasos,incidencia);

        free(array);
        limparLista_aux(pontos);
        limparLista_aux(raiz);
        return;
}

void fazCV(Lista casas, QuadTree quadras, char info[][50]){

        if(info[4][strlen(info[4])-1]== '\n'){
                info[4][strlen(info[4])-1] = '\0';
        }

        casa casa_atual = NULL;
        casa_atual = montaCasa(transfStringInt(info[1]), info[2], info[3], transfStringInt(info[4]), quadras); 
        
        if(casa_atual == NULL){
                removeCasa(casa_atual);
                return;
        }
        
        Info info_atual = montaInfo("cv","null", casa_atual);
        insertAfterLast(casas, info_atual);
}

void fazDQ(nodulo nodeCirc, char *path, Lista listQRY, QuadTree quadras, double r, int checkHash, HashTable cepXquadra){
        
        circulo circ = getModulo(getInfoQt(NULL,nodeCirc));

        if(quadras == NULL){
                return; 
        }

        delfTxt(path,getInfoQt(NULL,nodeCirc));
        Lista list = nosDentroRetanguloQt(quadras, retornaCirc_X(circ) - r, retornaCirc_Y(circ) - r, retornaCirc_X(circ) + r, retornaCirc_Y(circ) + r);
        //Lista list = nosDentroCirculoQt(quadras,retornaCirc_X(circ), retornaCirc_Y(circ), r);

        nodulo node = getFirst(list);

        while(node!=NULL){
                Modulo objeto = getModulo(getInfo(node));

                if(checkHash==0){       
                        retangulo ret = montaRetangulo(retornaQuadra_Cep(objeto), retornaQuadra_SW(objeto), retornaQuadra_W(objeto),retornaQuadra_H(objeto), retornaQuadra_X(objeto), retornaQuadra_Y(objeto),"olive","beige");
                        Info infoHash = montaInfo("rA",retornaQuadra_Cep(objeto), ret);
                        insertAfterLast(listQRY, infoHash); 
                }        

                //info pro txt
                delfTxt(path,getInfo(node));

                //remove a quadra
                removeHT(cepXquadra, retornaQuadra_Cep(objeto));
                nodulo qNode = getNoQt_byId(quadras,retornaQuadra_Cep(objeto));
                removeQt(quadras,qNode);

                node = getNext(node);
        }
        
        //adiciona o retangulo de consulta na lista qry
        retangulo retGrande = montaRetangulo("-9","1", 2*r, 2*r, retornaCirc_X(circ) - r, retornaCirc_Y(circ) - r,"black","none");
        Info infoCircGrande = montaInfo("r","-9", retGrande);
        insertAfterLast(listQRY,infoCircGrande); 

        //adiciona anel grosso na lista figuras 
        circulo fistCircle = montaCirculo("-11",retornaCirc_SW(circ),retornaCirc_Raio(circ)+8,retornaCirc_X(circ),retornaCirc_Y(circ),"yellow","yellow");
        Info infoFC = montaInfo("c","-10", fistCircle);
        insertAfterLast(listQRY, infoFC); 

        circulo secondCircle = montaCirculo("-10",retornaCirc_SW(circ),retornaCirc_Raio(circ)+3,retornaCirc_X(circ),retornaCirc_Y(circ),"goldenrod","goldenrod");

        Info infoSC = montaInfo("c","-11", secondCircle);
        insertAfterLast(listQRY, infoSC); 

        limparLista_aux(list);
}

void fazCAR(char *path, Lista listQRY, QuadTree hidrantes, QuadTree torresCel, QuadTree semaforos, QuadTree quadras, double x, double y, double w, double h){

        FILE *txt = fopen(path,"a+");
        double area=0;

        area = areaQuadra(path,listQRY,quadras,x,y,w,h);

        // fazer retangulo pedido

        retangulo ret = montaRetangulo("-9","1",w,h,x,y,"black","none");
        Info infoRet = montaInfo("r","-9",ret);
        insertAfterLast(listQRY,infoRet);

        // fazer linha vertical do ponto x,y ate o topo com a area ao lado

        double xc = x + w/2;
        double yc = y + h/2;

        retangulo line = montaRetangulo("-5","1",xc,0,xc,yc,"black","black");
        Info infoLine = montaInfo("l","-5", line);
        insertAfterLast(listQRY, infoLine);  

        char areaString[50];
        sprintf(areaString,"%.2f",area);

        texto text = montaTexto("-7",xc+2,0,"black","black", areaString,strlen(areaString)+2);
        Info infoText = montaInfo("t","-7",text);
        insertAfterLast(listQRY, infoText);  

        // txt = escrever a area total

        fprintf(txt, "Área total = %lf\n",area);

        fclose(txt);
}

void fazCBQ(char *path, double x, double y, double r, char *cstrk , QuadTree quadras){

        Modulo objeto;
        FILE *txt = fopen(path,"a+");

        Lista list = nosDentroCirculoQt(quadras, x, y, r);
        nodulo node = getFirst(list);
        nodulo aux;

        while(node != NULL){

                objeto = getModulo(getInfo(node));
                mudaCorBorda(node, cstrk);
                fprintf(txt,"CEP = %s\n",retornaQuadra_Cep(objeto));

                aux = node;
                node = getNext(node);
                removeNode(aux,list);
        }

        free(list);
        fclose(txt);
}

void fazDMP(char *path, char *t, char *sfx, QuadTree quadras, QuadTree hidrantes, QuadTree torresCel, QuadTree semaforos){

        char *pathSvg = concatenaSufixo(path, sfx, "svg");

        if(strcmp(t,"q")==0){
                recriaQt(quadras);
                imprimirQuadtree(quadras, pathSvg);
        }

        else if(strcmp(t,"h")==0){
                recriaQt(hidrantes);
                imprimirQuadtree(hidrantes, pathSvg);
        }

        else if(strcmp(t,"t")==0){
                recriaQt(torresCel);
                imprimirQuadtree(torresCel, pathSvg);
        }

        else if(strcmp(t,"s")==0){
                recriaQt(semaforos);
                imprimirQuadtree(semaforos, pathSvg);
        }

        free(pathSvg);

}

void fazMReg(Lista listQRY, Lista moradores, ponto *R, char *nomeReg, char *cpf){

        nodulo node = getFirst(moradores);
        ponto coord;

        while(node != NULL){

                Info infoMorador = getInfo(node);
                Modulo morador = getModulo(infoMorador);
                Pessoa pessoa = retornaMorador_Pessoa(morador);

                if(strcmp(cpf,retornaPessoa_Cpf(pessoa))==0){
                        coord = montaPonto(retornaPonto_X(retornaMorador_Ponto(morador)),retornaPonto_Y(retornaMorador_Ponto(morador))); 
                        carregarLinhaVertical(listQRY, infoMorador, nomeReg);
                        break;
                }

                node = getNext(node);
        }

        int indice = atoi(nomeReg+1);
        R[indice] = coord;
}

void fazEReg(Lista listQRY, HashTable cepXquadra, ponto *R, char *nomeReg, char *cep, char *face, int num){

        Info infoQuadra = searchHash(cepXquadra, cep);

        if(infoQuadra == NULL){
                return;
        }

        Modulo quadra = getModulo(infoQuadra);
        ponto coord = pontoCentral_Endereco(quadra, face, num);

        //insere a linha
        retangulo line = montaRetangulo("-5","1", retornaPonto_X(coord), 0, retornaPonto_X(coord), retornaPonto_Y(coord), "black", "black");
        Info infoLine = montaInfo("l","-5",line);
        insertAfterLast(listQRY, infoLine);
 
        //monta o texto do nome do registrador
        texto text = montaTexto("-6", retornaPonto_X(coord)+1, 1, "black", "black", nomeReg, strlen(nomeReg)+2);
        Info infoText = montaInfo("t","-6",text);

        insertAfterLast(listQRY, infoText);
        
        //insere no registrador com indice "indice"
        int indice = atoi(nomeReg+1);
        R[indice] = coord;
}       

void fazGReg(Lista listQRY, ponto *R ,QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree torresCel, QuadTree semaforos, QuadTree quadras, char *nomeReg, char *id){
        
        nodulo node = findNodeQt(circulos, retangulos, textos, hidrantes, torresCel, semaforos, quadras, id);

        if(node == NULL){
                return;
        }

        Info infoObjeto = getInfoQt(NULL, node);
        ponto coordAtual = retornaInfoCoord(infoObjeto);
        ponto coord = montaPonto(retornaPonto_X(coordAtual), retornaPonto_Y(coordAtual));

        carregarLinhaVertical(listQRY, infoObjeto, nomeReg);

        int indice = atoi(nomeReg+1);
        R[indice] = coord;
}

void fazXYReg(Lista listQRY, ponto *R, char *nomeReg, double x, double y){

        ponto coord = montaPonto(x,y);

        //monta a linha
        retangulo line = montaRetangulo("-5","1", retornaPonto_X(coord), 0, retornaPonto_X(coord), retornaPonto_Y(coord), "black", "black");
        Info infoLine = montaInfo("l","-5",line);
        insertAfterLast(listQRY, infoLine);
 
        //monta o texto do nome do registrador
        texto text = montaTexto("-6", retornaPonto_X(coord)+1, 1, "black", "black", nomeReg, strlen(nomeReg)+2);
        Info infoText = montaInfo("t","-6",text);

        insertAfterLast(listQRY, infoText);
        
        //insere no registrador com indice "indice"
        int indice = atoi(nomeReg+1);
        R[indice] = coord;
}

void fazP(Lista listQRY, ponto *R, Grafo grafo, char *pathTXT ,char *path, char *reg1, char *reg2, char *corMaisCurto, char *corMaisRapido){

        int posReg1 = atoi(reg1 + 1);
        int posReg2 = atoi(reg2 + 1);

        ponto coordR1 = montaPonto(retornaPonto_X(R[posReg1]), retornaPonto_Y(R[posReg1]));
        ponto coordR2 = montaPonto(retornaPonto_X(R[posReg2]), retornaPonto_Y(R[posReg2]));

        int posVerticeR1 = verticeMaisProximo(grafo, coordR1);
        int posVerticeR2 = verticeMaisProximo(grafo, coordR2);

        Info vertice1 = retornaVertice(grafo, posVerticeR1);
        Info vertice2 = retornaVertice(grafo, posVerticeR2);

        ponto coordVert1 = retornaVerticeCoord(vertice1);
        ponto coordVert2 = retornaVerticeCoord(vertice2);

        int posDestino = posVerticeR2;
        int *anterior = malloc(numeroDeVertices(grafo) * sizeof(int));

        double *distancia = dijkstra(grafo, posVerticeR1, 1, anterior); //caminho mais rapido

        if(anterior[posVerticeR2] == -1){
                FILE *txt = fopen(pathTXT, "a+");
                fprintf(txt,"Nao achou caminho entre os vertices\n");
                removePonto(coordR1);
                removePonto(coordR2);
                free(anterior);
                free(distancia);
                fclose(txt);
                return;
        }

        Lista trajeto = criarLista();

        Info vertice  = retornaVertice(grafo, posVerticeR1);
        insertAfterLast(trajeto, vertice);
        criarTrajeto(grafo, trajeto, anterior, posVerticeR2);
        imprimePathAnimacaoSvg(path, trajeto, grafo, 1, corMaisRapido);
        imprimirTrajetoTxt(trajeto, pathTXT, 1);
        limparLista_aux(trajeto);

        // comeca cmc
        
        free(distancia);
        distancia = dijkstra(grafo, posVerticeR1, 2, anterior); //caminho mais curto

        if(anterior[posVerticeR2] == -1){
                FILE *txt = fopen(pathTXT, "a+");
                fprintf(txt,"Nao achou caminho de R1 para R2\n");
                removePonto(coordR1);
                removePonto(coordR2);
                free(anterior);
                free(distancia);
                fclose(txt);
                return;
        }

        trajeto = criarLista();

        vertice  = retornaVertice(grafo, posVerticeR1);
        insertAfterLast(trajeto, vertice);

        criarTrajeto(grafo, trajeto, anterior, posVerticeR2);
        imprimePathAnimacaoSvg(path, trajeto, grafo, 2, corMaisCurto);
        imprimirTrajetoTxt(trajeto, pathTXT, 2);
        limparLista_aux(trajeto);
        removePonto(coordR1);
        removePonto(coordR2);

        free(anterior);
        free(distancia);
}

void fazCCV(Grafo grafo, Grafo *arvoreGeradoraMin,char *pathSvg){

        Grafo grafoNaoDirecionado = montaGrafoNaoDirecionado(grafo);
        *arvoreGeradoraMin = primMST(grafoNaoDirecionado);
        imprimirGrafo(grafo, pathSvg, "black");
        imprimirGrafo(*arvoreGeradoraMin, pathSvg, "orange");
        
        FILE *svg = fopen(pathSvg, "a+");
        fprintf(svg,"</svg>");
        fclose(svg);

        removeGrafo_Aux(grafoNaoDirecionado);
}

int retornaPosicionamentoAresta(Grafo grafo, Info aresta){

        char *idV1 = retornaArestaVertInicio(aresta);
        char *idV2 = retornaArestaVertFim(aresta);

        int *posicaoV1 = getModulo(searchHash(retornaHashTableGrafo(grafo), idV1));
        int *posicaoV2 = getModulo(searchHash(retornaHashTableGrafo(grafo), idV2));

        Info vertice1 = retornaVertice(grafo, *posicaoV1);
        Info vertice2 = retornaVertice(grafo, *posicaoV2);

        ponto coordV1 = retornaVerticeCoord(vertice1);
        ponto coordV2 = retornaVerticeCoord(vertice2);

        if(retornaPonto_X(coordV1) == retornaPonto_X(coordV2) && retornaPonto_Y(coordV1) > retornaPonto_Y(coordV2))
                return 0;
        
        else if(retornaPonto_X(coordV1) == retornaPonto_X(coordV2) && retornaPonto_Y(coordV1) < retornaPonto_Y(coordV2))
                return 1;

        else if(retornaPonto_X(coordV1) > retornaPonto_X(coordV2) && retornaPonto_Y(coordV1) == retornaPonto_Y(coordV2))
                return 2;

        else if(retornaPonto_X(coordV1) < retornaPonto_X(coordV2) && retornaPonto_Y(coordV1) == retornaPonto_Y(coordV2))
                return 3;

        return -1;

}

void interditarRua(char *path, char *cep, char *face, int numCasosFace){

        FILE *txt = fopen(path, "a+");
        fprintf(txt,"Trecho interditado = CEP: %s, FACE: %s, NÚMERO DE CASOS: %d\n", cep, face, numCasosFace);
        fclose(txt);
}

void fazBf(Lista listQRY, char *path, Grafo grafo, int maxCasos, HashTable cepXquadra){

        HashTable idvXi = retornaHashTableGrafo(grafo);

        for(int i=0;i<numeroDeVertices(grafo);i++){

                Info vertice1 = retornaVertice(grafo, i);
                Info vertice2;

                Lista arestas = retornaListaArestas(grafo, i);
                nodulo noduloAresta = getFirst(arestas);
                
                while(noduloAresta){
                        
                        Info aresta = getInfo(noduloAresta);
                        noduloAresta = getNext(noduloAresta);

                        int orientacao = retornaPosicionamentoAresta(grafo, aresta);

                        //sul
                        if(orientacao==0){

                                int resultado = 0;

                                if(strcmp(retornaLdir(aresta),"#")!=0){
                                        
                                        Info infoQuadra = searchHash(cepXquadra, retornaLdir(aresta));
                                        Quadra quad = getModulo(infoQuadra);

                                        double x1 = retornaQuadra_X(quad) - 1;
                                        double x2 = x1;
                                        double y1 = retornaQuadra_Y(quad);
                                        double y2 = retornaQuadra_Y(quad) + retornaQuadra_H(quad);

                                        if(numCasosFace(quad,"L") > maxCasos){
                                                interditarRua(path, retornaLdir(aresta), "L", numCasosFace(quad,"L"));
                                                carregaLinha(listQRY, x1, y1, x2, y2, "red");
                                                resultado++;
                                        }

                                }

                                if(strcmp(retornaLesq(aresta),"#")!=0){

                                        Info infoQuadra = searchHash(cepXquadra, retornaLesq(aresta));
                                        Quadra quad = getModulo(infoQuadra);

                                        double x1 = retornaQuadra_X(quad) + retornaQuadra_W(quad) + 1;
                                        double x2 = x1;
                                        double y1 = retornaQuadra_Y(quad);
                                        double y2 = retornaQuadra_Y(quad) + retornaQuadra_H(quad);

                                        if(numCasosFace(quad,"O") > maxCasos){
                                                interditarRua(path, retornaLesq(aresta), "O", numCasosFace(quad,"O"));
                                                carregaLinha(listQRY, x1, y1, x2, y2, "red");
                                                resultado++;    
                                        }

                                }

                                if(resultado>0){
                                        removeAresta(grafo, retornaVerticeId(vertice1), retornaArestaVertFim(aresta));
                                }
                        }

                        //norte
                        else if(orientacao==1){

                                int resultado = 0;
                                
                                if(strcmp(retornaLdir(aresta),"#")!=0){
                                        
                                        Info infoQuadra = searchHash(cepXquadra, retornaLdir(aresta));
                                        Quadra quad = getModulo(infoQuadra);

                                        double x1 = retornaQuadra_X(quad) + retornaQuadra_W(quad) + 1;
                                        double x2 = x1;
                                        double y1 = retornaQuadra_Y(quad);
                                        double y2 = retornaQuadra_Y(quad) + retornaQuadra_H(quad);

                                        if(numCasosFace(quad,"O") > maxCasos){
                                                interditarRua(path, retornaLdir(aresta), "O", numCasosFace(quad,"O"));
                                                carregaLinha(listQRY, x1, y1, x2, y2, "red");
                                                resultado++;
                                        }
                                        
                                }

                                if(strcmp(retornaLesq(aresta),"#")!=0){
                                        
                                        Info infoQuadra = searchHash(cepXquadra, retornaLesq(aresta));
                                        Quadra quad = getModulo(infoQuadra);

                                        double x1 = retornaQuadra_X(quad) - 1;
                                        double x2 = x1;
                                        double y1 = retornaQuadra_Y(quad);
                                        double y2 = retornaQuadra_Y(quad) + retornaQuadra_H(quad);

                                        if(numCasosFace(quad,"L") > maxCasos){
                                                interditarRua(path, retornaLesq(aresta), "L", numCasosFace(quad,"L"));
                                                carregaLinha(listQRY, x1, y1, x2, y2, "red");
                                                resultado++;
                                        }

                                }

                                if(resultado>0){
                                        removeAresta(grafo, retornaVerticeId(vertice1), retornaArestaVertFim(aresta));
                                }
                        }

                        //leste
                        else if(orientacao==2){

                                int resultado=0;

                                if(strcmp(retornaLdir(aresta),"#")!=0){

                                        Info infoQuadra = searchHash(cepXquadra, retornaLdir(aresta));
                                        Quadra quad = getModulo(infoQuadra);

                                        double x1 = retornaQuadra_X(quad);
                                        double x2 = retornaQuadra_X(quad) + retornaQuadra_W(quad);
                                        double y1 = retornaQuadra_Y(quad) + retornaQuadra_H(quad) + 1;
                                        double y2 = y1;

                                        if(numCasosFace(quad,"N") > maxCasos){
                                                interditarRua(path, retornaLdir(aresta), "N", numCasosFace(quad,"N"));
                                                carregaLinha(listQRY, x1, y1, x2, y2, "red");
                                                resultado++;
                                        }
                                        
                                }

                                if(strcmp(retornaLesq(aresta),"#")!=0){

                                        Info infoQuadra = searchHash(cepXquadra, retornaLesq(aresta));
                                        Quadra quad = getModulo(infoQuadra);

                                        double x1 = retornaQuadra_X(quad);
                                        double x2 = retornaQuadra_X(quad) + retornaQuadra_W(quad);
                                        double y1 = retornaQuadra_Y(quad) - 1;
                                        double y2 = y1;

                                        if(numCasosFace(quad,"S") > maxCasos){
                                                interditarRua(path, retornaLesq(aresta), "S", numCasosFace(quad,"S"));
                                                carregaLinha(listQRY, x1, y1, x2, y2, "red");
                                                resultado++;
                                        }

                                }

                                if(resultado>0){
                                        removeAresta(grafo, retornaVerticeId(vertice1), retornaArestaVertFim(aresta));
                                }

                        }

                        //oeste
                        else if(orientacao==3){

                                int resultado=0;

                                if(strcmp(retornaLdir(aresta),"#")!=0){

                                        Info infoQuadra = searchHash(cepXquadra, retornaLdir(aresta));
                                        Quadra quad = getModulo(infoQuadra);

                                        double x1 = retornaQuadra_X(quad);
                                        double x2 = retornaQuadra_X(quad) + retornaQuadra_W(quad);
                                        double y1 = retornaQuadra_Y(quad) - 1;
                                        double y2 = y1;

                                        if(numCasosFace(quad,"S") > maxCasos){
                                                interditarRua(path, retornaLdir(aresta), "S", numCasosFace(quad,"S"));
                                                carregaLinha(listQRY, x1, y1, x2, y2, "red");
                                                resultado++;
                                        }

                                }

                                if(strcmp(retornaLesq(aresta),"#")!=0){

                                        Info infoQuadra = searchHash(cepXquadra, retornaLesq(aresta));
                                        Quadra quad = getModulo(infoQuadra);

                                        double x1 = retornaQuadra_X(quad);
                                        double x2 = retornaQuadra_X(quad) + retornaQuadra_W(quad);
                                        double y1 = retornaQuadra_Y(quad) + retornaQuadra_H(quad) + 1;
                                        double y2 = y1;

                                        if(numCasosFace(quad,"N") > maxCasos){
                                                interditarRua(path, retornaLesq(aresta), "N", numCasosFace(quad,"N"));
                                                carregaLinha(listQRY, x1, y1, x2, y2, "red");
                                                resultado++;   
                                        }     
                                
                                }

                                if(resultado>0){
                                        removeAresta(grafo, retornaVerticeId(vertice1), retornaArestaVertFim(aresta));
                                }

                        }

                }
                
        }

}

void fazPb(Lista listQRY, ponto *R, Grafo grafo, char *pathTXT ,char *path, char *reg1, char *reg2, char *corMaisCurto){

        int posReg1 = atoi(reg1 + 1);
        int posReg2 = atoi(reg2 + 1);

        ponto coordR1 = montaPonto(retornaPonto_X(R[posReg1]), retornaPonto_Y(R[posReg1]));
        ponto coordR2 = montaPonto(retornaPonto_X(R[posReg2]), retornaPonto_Y(R[posReg2]));

        int posVerticeR1 = verticeMaisProximo(grafo, coordR1);
        int posVerticeR2 = verticeMaisProximo(grafo, coordR2);

        Info vertice1 = retornaVertice(grafo, posVerticeR1);
        Info vertice2 = retornaVertice(grafo, posVerticeR2);

        ponto coordVert1 = retornaVerticeCoord(vertice1);
        ponto coordVert2 = retornaVerticeCoord(vertice2);

        int posDestino = posVerticeR2;
        int *anterior = malloc(numeroDeVertices(grafo) * sizeof(int));

        double *distancia = dijkstra(grafo, posVerticeR1, 2, anterior); //caminho mais curto

        if(anterior[posVerticeR2] == -1){
                FILE *txt = fopen(path, "a+");
                fprintf(txt,"Nao achou caminho de R1 para R2\n");
                removePonto(coordR1);
                removePonto(coordR2);
                free(anterior);
                free(distancia);
                fclose(txt);
                return;
        }

        Lista trajeto = criarLista();
        Info vertice  = retornaVertice(grafo, posVerticeR1);
        insertAfterLast(trajeto, vertice);

        criarTrajeto(grafo, trajeto, anterior, posVerticeR2);
        imprimePathAnimacaoSvg(path, trajeto, grafo, 2, corMaisCurto);
        imprimirTrajetoTxt(trajeto, pathTXT, 2);
        limparLista_aux(trajeto);
        removePonto(coordR1);
        removePonto(coordR2);

        free(anterior);
        free(distancia);
}

void fazSP(Grafo grafo, ponto *R , Lista listQRY, Lista casas, char *path, char *pathTXT, char *reg1, char *reg2, char *cmc, char *cmr){

        int numPontos=0;

        nodulo nodeCasa = getFirst(casas);
        casa c;
        Info info_atual;

        Lista pontos = criarLista();

        while(nodeCasa!=NULL){

                Info informacao = getInfo(nodeCasa);
                c = getModulo(informacao);
                
                insertAfterLast(pontos, informacao);
                numPontos++; // Tamanho do vetor final de casas dentro do poligono
                
                nodeCasa = getNext(nodeCasa);
        }

        if(numPontos<3){
                limparLista_aux(pontos);
                return;
        }

        nodulo nodePonto = getFirst(pontos);
        
        Info *array = (Info*) malloc(sizeof(Info)*numPontos);
        int i=0;      

        //Cria o vetor de pontos que será inserido na tad do poligono

        while(nodePonto!=NULL){
                array[i] = getInfo(nodePonto);
                i++;
                nodePonto = getNext(nodePonto);
        }

        Lista raiz = envoltoriaConvexa(array, numPontos);

        int tam = listSize(raiz);
        i = 0;
        
        ponto *arrayFinal = criaArrayPontos(tam);

        nodulo node = getLast(raiz);
        
	while (node != NULL) 
	{ 
                Info info = getInfo(node);
		ponto p = retornaInfoCoord(info); 

                double x = retornaPonto_X(p);
                double y = retornaPonto_Y(p);
                arrayFinal[i] = montaPonto(x,y);
                i++;

		removeLast(raiz);
                node = getLast(raiz);
	} 

        poligono pol = montaPoligono(arrayFinal,tam);
        removeVerticesPoly(pol, getNoQt_root(retornaVerticesQtGrafo(grafo)));

        addCor(pol, "#FFFF00");
        FILE *svg = fopen(path,"a+");
        inserePoligono(svg, pol);
        fclose(svg);

        removePoligono(pol);
        free(array);
        limparLista_aux(pontos);
        limparLista_aux(raiz);

        fazP(listQRY, R, grafo, pathTXT, path, reg1, reg2, cmc, cmr);
}

void menuQRY(char *pathTXT, Grafo grafo, Grafo *arvoreGeradoraMin, ponto *R, Lista moradores, Lista listQRY, QuadTree circulos, QuadTree retangulos, QuadTree textos, QuadTree hidrantes, QuadTree torresCel, QuadTree semaforos, QuadTree quadras ,QuadTree regioes, QuadTree casas, QuadTree postos, Lista poligonos, char info[][50],int qtd, HashTable cepXquadra, HashTable cpfXpessoa ,HashTable codtXdesc, HashTable cpfXcep, Lista estabComerc, char **pathSvgAuxiliar){
        
        int i,j;

        escreveTxt(pathTXT, info, qtd);

        if(strcmp(info[0],"o?")==0){
                montaSobreposicao(pathTXT, listQRY, circulos, retangulos, info[1], info[2]);
        }

        else if(strcmp(info[0],"i?")==0){
                testeInterior(pathTXT, circulos, retangulos, listQRY, info[1], transfStringDouble(info[2]), transfStringDouble(info[3]));
        }

        else if(strcmp(info[0],"pnt")==0){
                mudaCor(pathTXT, circulos, retangulos, textos, info[1], info[2], info[3]);
                completarTxt(pathTXT);
        }

        else if(strcmp(info[0],"pnt*")==0){
                i =  transfStringInt(info[1]);
                j =  transfStringInt(info[2]);
                char id[30];
                strcpy(id, info[1]);
                
                arrumaString(info[4]);

                while(i <= j){
                        mudaCor(pathTXT, circulos,retangulos, textos, id, info[3], info[4]);
                        i++;
                        sprintf(id,"%d",i);
                }
                completarTxt(pathTXT);
        }

        else if(strcmp(info[0],"delf")==0){ 
                if(info[1][strlen(info[1])-1]== '\n'){
                        info[1][strlen(info[1])-1] = '\0';
                }           

                nodulo node = findNodeQt(circulos, retangulos, textos, hidrantes, torresCel, semaforos, quadras, info[1]);    

                if(node == NULL){
                        return;
                }

                else{
                        delfTxt(pathTXT, getInfoQt(NULL,node));

                        if(strcmp(retornaTipo(getInfoQt(NULL,node)), "c") == 0){
                                removeQt(circulos, node);
                        }else if(strcmp(retornaTipo(getInfoQt(NULL,node)), "r") == 0){
                                removeQt(retangulos, node);
                        }else{
                                removeQt(textos, node);
                        }

                        completarTxt(pathTXT);                        
                }
        }

        else if(strcmp(info[0],"delf*")==0){
                i =  transfStringInt(info[1]);
                j =  transfStringInt(info[2]);
                char id[30];
                strcpy(id, info[1]);

                while(i <= j){
                        
                        nodulo node = findNodeQt(circulos, retangulos, textos, hidrantes, torresCel, semaforos, quadras, id);    
                     
                        if(node!=NULL){

                                delfTxt(pathTXT, getInfoQt(NULL,node));
        
                                if(strcmp(retornaTipo(getInfoQt(NULL,node)), "c") == 0){
                                        removeQt(circulos, node);
                                }else if(strcmp(retornaTipo(getInfoQt(NULL,node)), "r") == 0){
                                        removeQt(retangulos, node);
                                }else{
                                        removeQt(textos, node);
                                }
                        }

                        i++;
                        sprintf(id,"%d",i);
                }
                completarTxt(pathTXT);
        }

        else if(strcmp(info[0],"del")==0){
                if(info[1][strlen(info[1])-1]== '\n'){
                        info[1][strlen(info[1])-1] = '\0';
                }           

                nodulo node = findNodeQt(circulos, retangulos, textos, hidrantes, torresCel, semaforos, quadras, info[1]);
               
                if(node == NULL){
                        return;
                }else{
                        delfTxt(pathTXT, getInfoQt(NULL,node));
                        carregarLinhaVertical(listQRY, getInfoQt(NULL,node), NULL);
                      
                        if(strcmp(retornaTipo(getInfoQt(NULL,node)), "q") == 0){
                                removeHT(cepXquadra,info[1]);
                                removeQt(quadras, node);
                        }else if(strcmp(retornaTipo(getInfoQt(NULL,node)), "rb") == 0){
                                removeQt(torresCel, node);
                        }else if(strcmp(retornaTipo(getInfoQt(NULL,node)), "s") == 0){
                                removeQt(semaforos, node);
                        }else if(strcmp(retornaTipo(getInfoQt(NULL,node)), "h") == 0){
                                removeQt(hidrantes, node);
                        }
                }
        }


        else if(strcmp(info[0],"crd?")==0){
                if(info[1][strlen(info[1])-1]== '\n'){
                        info[1][strlen(info[1])-1] = '\0';
                }

                nodulo node = findNodeQt(circulos, retangulos, textos, hidrantes, torresCel, semaforos, quadras, info[1]);

                if(node == NULL){
                        return;
                }else{
                        imprimeElemento(pathTXT, node);
                }
        }

        else if(strcmp(info[0],"cbq")==0){
                if(info[4][strlen(info[4])-1]== '\n'){
                        info[4][strlen(info[4])-1] = '\0';
                }

                fazCBQ(pathTXT,transfStringDouble(info[1]), transfStringDouble(info[2]), transfStringDouble(info[3]), info[4], quadras);
        }

        else if(strcmp(info[0],"car")==0){
                if(info[4][strlen(info[4])-1]== '\n'){
                        info[4][strlen(info[4])-1] = '\0';
                }
                fazCAR(pathTXT,listQRY,hidrantes, torresCel, semaforos, quadras, transfStringDouble(info[1]), transfStringDouble(info[2]), transfStringDouble(info[3]), transfStringDouble(info[4]));
        }

        else if(strcmp(info[0],"dq")==0){
                if(strcmp(info[1],"#")==0){

                        if(info[2][strlen(info[2])-1]== '\n'){
                                info[2][strlen(info[2])-1] = '\0';
                        }
                        
                        nodulo node =  findNodeQt(circulos, retangulos, textos, hidrantes, torresCel, semaforos, quadras, info[2]); //searchNode(figuras, hidrantes, semaforos, quadras, torresCel, info[2]);
                        
                        if(node==NULL){
                                return;
                        }
                        fazDQ(node, pathTXT, listQRY, quadras, transfStringDouble(info[3]), 0, cepXquadra);
                }else{
                        if(info[1][strlen(info[1])-1]== '\n'){
                                info[1][strlen(info[1])-1] = '\0';
                        }

                        nodulo node = findNodeQt(circulos, retangulos, textos, hidrantes, torresCel, semaforos, quadras, info[1]);
                        if(node==NULL){
                                return;
                        }
                        fazDQ(node, pathTXT, listQRY, quadras,transfStringDouble(info[2]), 1, cepXquadra);
                }
        }

        else if(strcmp(info[0],"cv")==0)
                fazCV(casas,quadras,info);

        else if(strcmp(info[0],"ci")==0)
                fazCI(pathTXT,casas, regioes, postos, poligonos, listQRY, info);

        else if(strcmp(info[0],"soc")==0)
                fazSOC(grafo, pathTXT, postos, casas, quadras, listQRY, info);

        else if(strcmp(info[0],"m?")==0)
                fazM(pathTXT, info[1] , moradores, cepXquadra);
        
        else if(strcmp(info[0],"dm?")==0)
                fazDM(pathTXT, info[1] , moradores, cpfXpessoa, listQRY);
        
        else if(strcmp(info[0],"de?")==0)
                fazDE(pathTXT, info[1] , estabComerc, codtXdesc);
        
        else if(strcmp(info[0],"mud")==0)
                fazMUD(pathTXT, info[1], info[2], info[3], transfStringInt(info[4]), info[5], cpfXcep, cpfXpessoa ,cepXquadra, moradores, listQRY);

        else if(strcmp(info[0],"eplg?")==0)
                fazEPLG(pathTXT, info[1], transfStringDouble(info[2]), transfStringDouble(info[3]), transfStringDouble(info[4]), transfStringDouble(info[5]), estabComerc,  codtXdesc, listQRY);
        
        else if(strcmp(info[0],"catac")==0)
                fazCATAC(pathTXT, transfStringDouble(info[1]), transfStringDouble(info[2]), transfStringDouble(info[3]), grafo, moradores, estabComerc, quadras, hidrantes, torresCel, semaforos, listQRY, codtXdesc, cepXquadra, cpfXpessoa);
        
        else if(strcmp(info[0],"dmprbt")==0)
                fazDMP(pathTXT, info[1],info[2], quadras, hidrantes, torresCel, semaforos);
        
        else if(strcmp(info[0],"@m?")==0)
                fazMReg(listQRY, moradores, R, info[1], info[2]);

        else if(strcmp(info[0],"@e?")==0)
                fazEReg(listQRY, cepXquadra, R, info[1], info[2], info[3], atoi(info[4]));

        else if(strcmp(info[0],"@g?")==0)
                fazGReg(listQRY, R, circulos, retangulos, textos, hidrantes, torresCel, semaforos, quadras, info[1], info[2]);

        else if(strcmp(info[0],"@xy")==0)
                fazXYReg(listQRY, R, info[1], transfStringDouble(info[2]), transfStringDouble(info[3]));

        else if(strcmp(info[0],"ccv")==0){
                char *pathSvg = concatenaSufixo(pathTXT, info[1], "svg");
                FILE *svg = fopen(pathSvg, "w+");
                transfSVGgeo(svg, circulos, retangulos, textos, hidrantes, quadras, torresCel, semaforos, postos);
                fclose(svg);
                fazCCV(grafo, arvoreGeradoraMin, pathSvg);
                free(pathSvg);
        }

        else if(strcmp(info[0],"bf")==0)
                fazBf(listQRY, pathTXT, grafo, transfStringInt(info[1]), cepXquadra);
        
        else if(strcmp(info[0],"p?")==0){

                *pathSvgAuxiliar = criarPathAuxiliar(pathTXT, *pathSvgAuxiliar, info[1]);
                FILE *svg = fopen(*pathSvgAuxiliar, "a+");
                
                fseek(svg, 0, SEEK_END);
                long size = ftell(svg);

                if(size ==0){
                        transfSVGgeo(svg, circulos, retangulos, textos, hidrantes, quadras, torresCel, semaforos, postos);
                }
                                
                fclose(svg);
                fazP(listQRY, R, grafo, pathTXT, *pathSvgAuxiliar, info[2], info[3], info[4], info[5]);
        }

        else if(strcmp(info[0],"sp?")==0){

                *pathSvgAuxiliar = criarPathAuxiliar(pathTXT, *pathSvgAuxiliar, info[1]);
                FILE *svg = fopen(*pathSvgAuxiliar, "a+");
                
                fseek(svg, 0, SEEK_END);
                long size = ftell(svg);

                if(size ==0){
                        transfSVGgeo(svg, circulos, retangulos, textos, hidrantes, quadras, torresCel, semaforos, postos);
                }
                                
                fclose(svg);
                fazSP(grafo, R, listQRY, casas , *pathSvgAuxiliar, pathTXT, info[2], info[3], info[4], info[5]);
        }

        else if(strcmp(info[0],"pb?")==0){

                *pathSvgAuxiliar = criarPathAuxiliar(pathTXT, *pathSvgAuxiliar, info[1]);
                FILE *svg = fopen(*pathSvgAuxiliar, "a+");
                
                fseek(svg, 0, SEEK_END);
                long size = ftell(svg);

                if(size ==0){
                        transfSVGgeo(svg, circulos, retangulos, textos, hidrantes, quadras, torresCel, semaforos, postos);
                }
                                
                fclose(svg);
                fazPb(listQRY, R, *arvoreGeradoraMin, pathTXT, *pathSvgAuxiliar, info[2], info[3], info[4]);
        }

}
