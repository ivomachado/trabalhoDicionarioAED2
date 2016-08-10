#include "stopwords.h"
#include "dicionarioestatico.h"
#include "stringdicionarioutils.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    TDicionarioEstatico * dict;
}TDadoStopWordManager;

static int isStopWord(TStopWordManager * stop, char * word) {
    TDadoStopWordManager * d = (TDadoStopWordManager*)stop->dado;
    return d->dict->buscar(d->dict, word) != NULL;
}

TDadoStopWordManager * criarDadoStopWordManager() {
    TDadoStopWordManager * d = (TDadoStopWordManager*)malloc(sizeof(TDadoStopWordManager));
    FILE *fp = fopen("./base/stop_words", "r");
    char pal[100];
    char *aux;
    void *stop_words[400];
    int word_count = 0;
    while(lerPalavra(fp, pal)) {
        aux = (char*)malloc(sizeof(strlen(pal) + 1));
        strcpy(aux,pal);
        stop_words[word_count++] = aux;
    }
    d->dict = criarDicionarioEstatico(stop_words, stop_words, word_count, comparaTuplaString);
    free(stop_words);
    return d;
}

TStopWordManager * criarStopWordManager() {
    TStopWordManager *stop = malloc(sizeof(TStopWordManager));
    stop->dado = criarDadoStopWordManager();
    stop->isStopWord = isStopWord;
    return stop;
}
