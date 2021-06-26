#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathment.h"

typedef struct Paths{

    char * entrada;
    char * saida;
    char * geo;
    char * qry;
    char * ec;
    char * pm;
    char * via;

    // entrada
    char * geoEntrada;
    char * qryEntrada;
    char * ecEntrada;
    char * pmEntrada;
    char * viaEntrada;

    //files name
    char * geoFile;
    char * qryFile;
    char * viaFile;

    //Saida dos svg
    char * svgGeoSaida;
    char * svgQrySaida;

    //txt qry
    char * txtQrySaida;

} Paths;

typedef struct Frag {
    char ** array;
    size_t index;
} Frag;

char *path_Via(diretorio caminhos){
        Paths *dir = (Paths*) caminhos;

        return dir->viaEntrada;
}

char *path_Ec(diretorio caminhos){
        Paths *dir = (Paths*) caminhos;

        return dir->ecEntrada;
}

char *path_Pm(diretorio caminhos){
        Paths *dir = (Paths*) caminhos;

        return dir->pmEntrada;
}

char *path_nomeArqQry(diretorio caminhos){
        Paths *dir = (Paths*) caminhos;

        return dir->qry;
}

char *path_pathGeo(diretorio caminhos){
        Paths *dir = (Paths*) caminhos;

        return dir->geoEntrada;
}

char *path_pathQry(diretorio caminhos){
        Paths *dir = (Paths*) caminhos;
        
        return dir->qryEntrada;
}

char *path_pathSvg_geo(diretorio caminhos){
        Paths *dir = (Paths*) caminhos;

        return dir->svgGeoSaida;
}

char *path_pathSvg_qry(diretorio caminhos){
        Paths *dir = (Paths*) caminhos;

        return dir->svgQrySaida;
}

char *path_pathTxt(diretorio caminhos){
        Paths *dir = (Paths*) caminhos;

        return dir->txtQrySaida;
}

char * setParam(int pos, char ** argv){
    char * string = NULL; 

    if(argv[pos+1] != NULL){
        string = (char*) malloc( strlen( argv[pos+1] ) + 1 );
        strcpy(string, argv[pos+1]); 
    }

    return string; //retorna o add da string
}

char * concatString_text(char ** array, size_t start, size_t arraySize){
    int i = start;
    int sizeCounter = 0;


    for(i; i < arraySize; i++){
        sizeCounter += strlen(array[i])+1;
    }

    sizeCounter += 1;

    char * tmpString = (char *) malloc(sizeCounter * sizeof(char));
    
    memset(tmpString, '\0', sizeCounter);

    i = start;

    for(i; i < arraySize; i++){
        strcat(tmpString, " ");
        strcat(tmpString, array[i]);
    }

    strcat(tmpString, "\0");
    return tmpString;
}

void _init_paths(diretorio caminhos, int argc, char ** argv) {  
    int i = 1;  //pula o nome do programa

    for(i; i < argc; i++){

        Paths * dirPaths = (Paths*) caminhos;   

        if( !strcmp(argv[i], "-e") ){
            dirPaths->entrada = setParam(i, argv);
            i++;
        }
        
        if( !strcmp(argv[i], "-o") ){
            dirPaths->saida = setParam(i, argv);
            i++;
        }
        
        if( !strcmp(argv[i], "-f") ){
            dirPaths->geo = setParam(i, argv);
            i++;
        }
        
        if( !strcmp(argv[i], "-q") ){
            dirPaths->qry = setParam(i, argv);
            i++;
        }

        if( !strcmp(argv[i], "-pm") ){
            dirPaths->pm = setParam(i, argv);
            i++;
        }

        if( !strcmp(argv[i], "-ec") ){
            dirPaths->ec = setParam(i, argv);
            i++;
        }   

        if( !strcmp(argv[i], "-v") ){
            dirPaths->via = setParam(i, argv);
            i++;
        }   
    }
}

Frags fragString(const char * string, const char * delim){
    char * buffer;
    Frag * array = (Frag *) malloc(sizeof(Frag));    
    int size = strlen(string);

    array->index = 0;

    buffer = (char *) malloc(size + 1);
    strcpy(buffer, string);

    char * ptr;
    ptr = strtok(buffer, delim);

    while(ptr != NULL){
        array->index++;
        ptr = strtok(NULL, delim);
    }
  
    memset(buffer, '\0', size+1);  
    strcpy(buffer, string);        

    array->array = (char **) malloc((array->index) * sizeof(char *)); 

    int i = 0;
    ptr = strtok(buffer, delim);

    while(ptr != NULL){
        array->array[i] = malloc(strlen(ptr) + 1);
        strcpy(array->array[i], ptr);

        i++;
        ptr = strtok(NULL, delim);
    }

    free(buffer);
    return array;
}

void free_fragString(Frags vector){

    Frag *array = (Frag*) vector;   
    size_t index = array->index;

    int i = 0;
    for(i; i < index; i++){
        free(array->array[i]);
    }

    free(array->array);
    free(array);
}

char * getFileName(char * path){
    char * fileName;

    Frag * Strings = fragString(path, "/");
    size_t StrLen = Strings->index;

    fileName = (char *) malloc(strlen( Strings->array[ StrLen - 1]) + 1); //
    strcpy(fileName,  Strings->array[ StrLen - 1 ]);

    free_fragString(Strings);

    return fileName;
}

void _getFileName_paths(diretorio caminhos){

    Paths *curPaths = (Paths*) caminhos;    

    curPaths->geoFile = getFileName(curPaths->geo); 
    
    if(curPaths->qry){
        curPaths->qryFile = getFileName(curPaths->qry);
    }
}

int findString(const char * string, const char * find , int start){
    
    if(string == NULL || find == NULL || start < 0){ return -2;} 

    int length = strlen(string);
    int findStrLength = strlen(find);

    if(start < length && length >= findStrLength){
        for(int i = start; i < length; i++){
            int match = 0;

            //primeira ocorrencia
            if(string[i] == find[0]){
                int j = 1; 
                match = 1;

                //verifica as proximas ocorrencias
                for(j; j < findStrLength; j++){
                    if(string[i+j] != find[j]){
                        match = 0;
                        
                        j = findStrLength; 
                    }
                }
            }

            if(match){ return i;}
        }
    }

    
    //se nao deu match com a find entao retorna nao encontrado
    return -1;

    //return -2 => error nos parametros
    //return -1 => nao encontrado;
}

char * concatFilePath(const char * entryPath, const char * filePath){
    char * path = NULL;
    char * tmpPath = NULL;

    size_t entryLen = 0; 
    size_t fileLen = strlen(filePath);

    int entryExists = 0;
    
    if(entryPath != NULL){
        entryLen = strlen(entryPath);

        entryExists = 1;

        if(findString(entryPath, "/", entryLen-1) != (entryLen - 1)){  
            tmpPath = (char *) malloc((entryLen + 2) * sizeof(char));
            strcpy(tmpPath, entryPath);
            strcat(tmpPath, "/");
        }else{
            tmpPath = (char *) malloc((entryLen + 1) * sizeof(char));
            strcpy(tmpPath, entryPath);
        }
    }


    if(entryExists){
        //.
        if(findString(filePath, ".", 0) == 0){
            //..
            if(findString(filePath, ".", 1) == 0){
                path = (char *) realloc(tmpPath, (strlen(tmpPath) + fileLen - 2) * sizeof(char));
                strcat(path, &filePath[3]); 
            }else{
                path = (char *) realloc(tmpPath,(strlen(tmpPath) + fileLen - 1) * sizeof(char));
                strcat(path, &filePath[2]); 
            }

        }else if(findString(filePath, "/",0) == 0){ // 
            
            path = (char *) realloc(tmpPath, (strlen(tmpPath) + fileLen) * sizeof(char));
            strcat(path, &filePath[1]); 
        }else{
            path = (char *) realloc(tmpPath, (strlen(tmpPath) + fileLen + 1) * sizeof(char));
            strcat(path, filePath);
        }

    }else{
        
        path = (char *) malloc((fileLen + 1) * sizeof(char));
        strcpy(path, filePath);
    }

    return path;
}

void _setInOut_paths(diretorio caminhos){

     Paths *curPaths = (Paths*) caminhos;   

     if(curPaths->entrada){
        curPaths->geoEntrada = concatFilePath(curPaths->entrada, curPaths->geo);
        
        if(curPaths->qry){curPaths->qryEntrada = concatFilePath(curPaths->entrada, curPaths->qry);}
        if(curPaths->ec){ curPaths->ecEntrada = concatFilePath(curPaths->entrada, curPaths->ec);}
        if(curPaths->pm){ curPaths->pmEntrada = concatFilePath(curPaths->entrada, curPaths->pm);}
        if(curPaths->via){ curPaths->viaEntrada = concatFilePath(curPaths->entrada, curPaths->via);}
    }else{
        curPaths->geoEntrada = concatFilePath(NULL, curPaths->geo);
        
        if(curPaths->qry){ curPaths->qryEntrada = concatFilePath(NULL, curPaths->qry);}
        if(curPaths->ec){ curPaths->ecEntrada = concatFilePath(NULL, curPaths->ec);}
        if(curPaths->pm){ curPaths->pmEntrada = concatFilePath(NULL, curPaths->pm);}
        if(curPaths->via){ curPaths->viaEntrada = concatFilePath(NULL, curPaths->via);}

    }
}

char * extFileTo(const char * string, int ch, const char * newExt){
    char * newString = malloc(strlen(string) + 1);
    strcpy(newString, string);

    char * ptrCh = strrchr(newString, ch);

    if(ptrCh){
        int len = strlen(ptrCh);
        int i;
        for(i = 1; i < len; i++){
            ptrCh[i] = newExt[i];
        }
    }

    return newString;
}

void _createSvgGeoPath_paths(diretorio caminhos){

     Paths *curPaths = (Paths*) caminhos;

    char * tmpExt = extFileTo(curPaths->geoFile, '.', ".svg");
    curPaths->svgGeoSaida = concatFilePath(curPaths->saida, tmpExt);
    
    free(tmpExt);
}

char * _appendExtension(char * path_noExt, const char * ext){
    char * svgQry = (char *) malloc( strlen(path_noExt) + strlen(ext) + 1 );

    strcpy(svgQry, path_noExt);
    strcat(svgQry, ext);

    return svgQry;
}

void _createNewPaths_paths(diretorio caminhos){

    _createSvgGeoPath_paths(caminhos);

    Paths *curPaths = (Paths*) caminhos;

    if(curPaths->qry != NULL){

        Frag * Strings_geo = (Frag*) fragString(curPaths->geoFile, ".");
        Frag * Strings_qry = (Frag*) fragString(curPaths->qryFile, ".");

        char * fileName_noExt = malloc( strlen(Strings_geo->array[0]) + strlen(Strings_qry->array[0]) + 2 );

        strcpy(fileName_noExt, Strings_geo->array[0]);
        
        strcat(fileName_noExt, "-");
        strcat(fileName_noExt, Strings_qry->array[0]); 
        
        char * svgNoext = _appendExtension(fileName_noExt, ".svg");
        char * txtNoext = _appendExtension(fileName_noExt, ".txt");

        if(curPaths->saida){
            curPaths->svgQrySaida = concatFilePath( curPaths->saida, svgNoext );
            curPaths->txtQrySaida = concatFilePath( curPaths->saida, txtNoext );
        } else{
            printf("O diretorio de saída não existe\n");
        }

        free(svgNoext);
        free(txtNoext);
        free(fileName_noExt);
        free_fragString(Strings_geo);
        free_fragString(Strings_qry);
    }
}

diretorio setPaths(int argc, char ** argv){

    Paths * auxPaths = (Paths *) malloc(sizeof(Paths));

    auxPaths->entrada     = NULL; //-e
    auxPaths->saida       = NULL; //-o
    auxPaths->geo         = NULL; //-f
    auxPaths->qry         = NULL; //-q
    auxPaths->ec          = NULL; //-ec
    auxPaths->pm          = NULL; //-pm
    auxPaths->via         = NULL; //-via

    auxPaths->geoFile     = NULL;
    auxPaths->qryFile     = NULL;

    auxPaths->qryEntrada  = NULL; // -e + -f
    auxPaths->geoEntrada  = NULL; // -e + -q
    auxPaths->ecEntrada   = NULL;
    auxPaths->pmEntrada   = NULL;
    auxPaths->viaEntrada  = NULL;


    auxPaths->svgGeoSaida = NULL; // -o + -e + .svg
    auxPaths->svgQrySaida = NULL; // -o + -q + '-' + e + '.svg'
    auxPaths->txtQrySaida = NULL; // -o + -q + '-' + e + '.txt'

    _init_paths(auxPaths, argc, argv);

    if( !(auxPaths->geo && auxPaths->saida) ){
        free_paths(auxPaths);
        return NULL;
    }


    _getFileName_paths(auxPaths); //pega o file de geo e de qry
    _setInOut_paths(auxPaths);   

    _createNewPaths_paths(auxPaths);

    //printf("\n pm = %s", auxPaths->pmEntrada);
    //printf("\n ec = %s",auxPaths->ecEntrada);

    return auxPaths;
}


void free_paths(diretorio caminhos){

    Paths *path = (Paths*) caminhos;

    free(path->entrada);
    free(path->saida);

    free(path->geo);
    free(path->qry);
    free(path->ec);
    free(path->pm);
    free(path->via);

    free(path->qryEntrada);
    free(path->geoEntrada);
    free(path->ecEntrada);
    free(path->pmEntrada);
    free(path->viaEntrada);

    free(path->geoFile);
    free(path->qryFile);

    free(path->svgGeoSaida);
    free(path->svgQrySaida);
    free(path->txtQrySaida);

    free(path);
}

char *criarPathAuxiliar(char *path, char *pathAuxiliar, char *sufixo){

    if(strcmp(pathAuxiliar,"vazio")==0){
        pathAuxiliar = concatenaSufixo(path, sufixo, "svg");
    }else{
        if(strcmp(sufixo, "-")!=0){

            char *pathSvg = concatenaSufixo(path, sufixo, "svg");

            if(strcmp(pathSvg, pathAuxiliar)!=0){
                FILE *svg = fopen(pathAuxiliar, "a+");
                fprintf(svg, "\n</svg>");
                fclose(svg);
                pathAuxiliar = pathSvg;
            }
        }
    }

    return pathAuxiliar;
}

char *concatenaSufixo(char *saidaQry, char *sufixo, char *tipo){
    
    int len = strlen(saidaQry)+strlen(sufixo)+ 2;
    char *pathSufixo = malloc(sizeof(char) * len);

    memset(pathSufixo, '\0', len);
    strcpy(pathSufixo, saidaQry);

    pathSufixo[strlen(saidaQry)-4] = '-';
    pathSufixo[strlen(saidaQry)-3] = '\0';

    strcat(pathSufixo,sufixo);

    if(strcmp(tipo, "svg")==0){
        strcat(pathSufixo,".svg");
    }else if(strcmp(tipo, "txt")==0){
        strcat(pathSufixo,".txt");
    }
    
    return pathSufixo;
    
}
