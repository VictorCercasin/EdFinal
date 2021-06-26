#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

typedef struct s{
        char *str;
} string;

String montaString(char *s){

        string* str = malloc(sizeof(string));
        str->str = (char *) malloc((strlen(s)+1));

        strcpy(str->str, s);

        return str;
}

void alteraString(String s, char *novaString){
        string* str = (string*) s;
        free(str->str);

        str->str = (char *) malloc(sizeof(char)*((strlen(novaString)+1)));
        strcpy(str->str, novaString);
}

char *getString(String s){
        string* str = (string*) s;

        return str->str;
}

void removeString(String s){
        string* str = (string*) s;
        
        free(str->str);
        free(str);
}