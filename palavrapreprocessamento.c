#include "palavrapreprocessamento.h"
#include "dicionariosemiestatico.h"
#include "primitivodicionarioutils.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    char * palavra;
    TDicionarioSemiEstatico *paginas;
    int ocorrenciasGlobais;
}TDadoPalavraPreprocessamento;

static int *getOcorrenciasPagina(TPalavraProcessamento *palavra, int pag) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    int *k; 
    int *ocorrencias;
    ocorrencias = d->paginas->buscar(d->paginas, &pag);
    if(ocorrencias == NULL) {
        k = (int*)malloc(sizeof(int));
        *k = pag;
        ocorrencias = calloc(1, sizeof(int));
        d->paginas->inserir(d->paginas, k, ocorrencias);
    }
    return ocorrencias;
}

static int incrementarPagina(TPalavraProcessamento *palavra, int pag) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    int *ocorrencias = getOcorrenciasPagina(palavra, pag);
    *ocorrencias += 1;
    d->ocorrenciasGlobais++;
    return *ocorrencias;
}

static int decrementarPagina(TPalavraProcessamento *palavra, int pag) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    int *ocorrencias = getOcorrenciasPagina(palavra, pag);
    if(*ocorrencias > 0) {
        *ocorrencias -= 1;
        d->ocorrenciasGlobais--;
    }
    return *ocorrencias;
}

static int ocorrenciasPagina(TPalavraProcessamento *palavra, int pag) {
    return *getOcorrenciasPagina(palavra, pag);
}

static int ocorrenciasTotais(TPalavraProcessamento *palavra) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    return d->ocorrenciasGlobais;
}

TDadoPalavraPreprocessamento * criarDadoPalavraPreprocessamento() {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)malloc(sizeof(TDadoPalavraPreprocessamento));
    d->paginas = criarDicionarioSemiEstatico(50, intHashing, comparaTuplaChaveInteger);
    d->ocorrenciasGlobais = 0;
    return d;
}

TPalavraProcessamento * criarPalavraProcessamento() {
    TPalavraProcessamento *p = (TPalavraProcessamento*)malloc(sizeof(TPalavraProcessamento));
    p->dado = criarDadoPalavraPreprocessamento();
    p->incrementarPagina = incrementarPagina;
    p->decrementarPagina = decrementarPagina;
    p->ocorrenciasPagina = ocorrenciasPagina;
    p->ocorrenciasTotais = ocorrenciasTotais;
    return p;
}
