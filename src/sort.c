#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

static ponto p0;

double distSq(ponto p1, ponto p2) 
{ 
	double result = (retornaPonto_X(p1) - retornaPonto_X(p2)) * (retornaPonto_X(p1) - retornaPonto_X(p2)) + 
		(retornaPonto_Y(p1) - retornaPonto_Y(p2)) * (retornaPonto_Y(p1) - retornaPonto_Y(p2)); 

	return result;
}

int orientation(ponto p, ponto q, ponto r){ 
	double val = (retornaPonto_Y(q) - retornaPonto_Y(p)) * (retornaPonto_X(r) - retornaPonto_X(q)) - 
			(retornaPonto_X(q) - retornaPonto_X(p)) * (retornaPonto_Y(r) - retornaPonto_Y(q)); 
            
	if (val == 0) return 0; // colinear 
	return (val > 0)? 1: 2; // horario ou anti-horario 
} 

int compare(ponto *vp1, ponto *vp2){ 
    ponto *p1 = vp1; 
    ponto *p2 = vp2; 

    // encontra a orientacao
    int o = orientation(p0, *p1, *p2); 
    if (o == 0) 
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 

    return (o == 2)? 1 : 0; 
} 

int compare_qSort(void *vp1, void *vp2){ 

    Info *info1 = (Info*) vp1;
    Info *info2 = (Info*) vp2;

    ponto p1 = retornaInfoCoord(*info1);
    ponto p2 = retornaInfoCoord(*info2);

    // encontra a orientacao
    int o = orientation(p0, p1, p2); 
    if (o == 0) 
        return (distSq(p0, p2) >= distSq(p0, p1))? -1 : 1; 

    return (o == 2)? -1 : 1; 
} 

void swapPoint_qSort(void *p1, void *p2){

    char buf[sizeof(Info)]; 

    memcpy(buf, p1, sizeof(Info)); 
    memcpy(p1, p2, sizeof(Info)); 
    memcpy(p2, buf, sizeof(Info)); 
    
} // int -> void

void swapPoint(Info *p1, Info *p2){
    ponto *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
} // int -> void

Lista envoltoriaConvexa(Info *array, int n){
        
        double ymin = retornaPonto_Y(retornaInfoCoord(array[0]));
        int min = 0;  // Pega o y do primeiro ponto e depois vai comparando até achar o menor y

        for (int i = 1; i < n; i++){
        
                int y = retornaPonto_Y(retornaInfoCoord(array[i]));

	        if ((y < ymin) || (ymin == y && retornaPonto_X(retornaInfoCoord(array[i])) < retornaPonto_X(retornaInfoCoord(array[min])))) {
                        ymin = retornaPonto_Y(retornaInfoCoord(array[i])), min = i; 
                }

        }

        swapPoint(&array[0], &array[min]); 

        p0 = retornaInfoCoord(array[0]);

        quickSort(array,1,n-1);


        int m = 1; 
        
        for (int i=1; i<n; i++){

                while (i < n-1 && orientation(p0, retornaInfoCoord(array[i]), retornaInfoCoord(array[i+1])) == 0){
                        i++;
                }
                
                array[m] = array[i];
                m++;
        }


        if (m < 3) return NULL; 

        Lista raiz = criarLista();

        Info i0 = array[0];
        Info i1 = array[1];
        Info i2 = array[2];
       
        insertAfterLast(raiz,i0);
        insertAfterLast(raiz,i1);
        insertAfterLast(raiz,i2);

        for (int i = 3; i < m; i++){
                nodulo node_last = getLast(raiz);
                nodulo node_previous = getPrevious(node_last);
                
                Info t = getInfo(node_last);
                Info ntp = getInfo(node_previous);
	        while (orientation(retornaInfoCoord(ntp), retornaInfoCoord(t), retornaInfoCoord(array[i])) != 2){
                        
                        removeLast(raiz);
                        node_last = getLast(raiz);
                        node_previous = getPrevious(node_last);
                        t = getInfo(node_last);
                        ntp = getInfo(node_previous);
                }

	        insertAfterLast(raiz,array[i]);
	}
        
        return raiz;

}

void quickSort(void *array, int low, int high) { 

	if(low>=high){
        return;
    }

    Info at,a3;
    int last;
    int middle = (low+high)/2;

    Info a1 = (array + (low * sizeof(Info)));
    Info ar = (array + (middle * sizeof(Info)));

    swapPoint_qSort(a1,ar);
    last = low;

    for(int i=low+1;i<=high;i++){

        at = (array+(i*sizeof(Info)));

        if(compare_qSort(a1,at)>0){
            ++last;
            a3 = (array + (last * sizeof(Info)));
            swapPoint_qSort(at,a3);
        }
    }

    a3 = (array + (last*sizeof(Info)));

    swapPoint_qSort(a1,a3);

    quickSort(array, low, last - 1); 
    quickSort(array, last + 1, high); 

} 

ponto *mergeSort(ponto *array, int n, int k, ponto ref){
    
    ponto *primeiros = (ponto*)malloc(sizeof(ponto)*k);
    ponto atual[k];

    int count=0, menorIndice, indice[k];
    double menor, dist;

    for(int i = 0;i < k;i++){
        indice[i]=0;
    }

    while(count<k){
        for(int i = 0; i < k; i++){
            if( (i + (k * indice[i])) < n){
                atual[i] = array[i+k*indice[i]];
            }else{
                atual[i] = NULL;
            }
        }
        
        for(int i=0; i<k; i++){

            if(atual[i] == NULL){
                dist = -1;
            }else{
                dist = distSq(ref,atual[i]);
            }

            if(i!=0){
                if(dist < menor && dist >= 0){
                    menor = dist;
                    menorIndice = i;
                }
            }else{
                menor = dist;
                menorIndice = i;
            }
        }

        double x = retornaPonto_X(atual[menorIndice]);
        double y = retornaPonto_Y(atual[menorIndice]);

        ponto p = montaPonto(x,y);

        primeiros[count] = p;
        indice[menorIndice]++;
        count++;
    }
    
    return primeiros;
}

ponto *shellSort(ponto *vet, int size, int k, ponto ref, int *tamanhoResultado) {
    
	int i , j;

	if(size <= k ){
                *tamanhoResultado = size;
                return vet;
	}

        for (int i = k; i < size; i++){
         
                double temp = distSq(ref,vet[i]);
	        ponto tempPonto = vet[i];
                
                int j = i-k;
                while (j >= 0 && temp < distSq(vet[j],ref)) {
                        vet[j + k] = vet[j];
                        j -= k;
                }
              
                vet[j+k] = tempPonto;
        }
        
        ponto *primeiros = mergeSort(vet,size,k,ref);
        *tamanhoResultado = k;
        return primeiros;
}