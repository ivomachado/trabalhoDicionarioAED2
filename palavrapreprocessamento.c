#include "palavrapreprocessamento.h"
#include "dicionariosemiestatico.h"
#include "primitivodicionarioutils.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    char * palavra;
    TDicionarioSemiEstatico *paginas;
    int numeroPaginas;
    int ocorrenciasGlobais;
}TDadoPalavraPreprocessamento;

static int *getOcorrenciasPagina(TPalavraProcessamento *palavra, int pag, int criar) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    int *k; 
    int *ocorrencias = d->paginas->buscar(d->paginas, &pag);
    if(ocorrencias == NULL && criar) {
        k = (int*)malloc(sizeof(int));
        *k = pag;
        ocorrencias = calloc(1, sizeof(int));
        d->paginas->inserir(d->paginas, k, ocorrencias);
        d->numeroPaginas++;
    }
    return ocorrencias;
}

static int incrementarPagina(TPalavraProcessamento *palavra, int pag) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    int *ocorrencias = getOcorrenciasPagina(palavra, pag, 1);
    *ocorrencias += 1;
    d->ocorrenciasGlobais++;
    return *ocorrencias;
}

static int ocorrenciasPagina(TPalavraProcessamento *palavra, int pag) {
    int * resultado = getOcorrenciasPagina(palavra, pag, 0); 
    if(resultado != NULL) return *resultado;
    else return 0;
}

static int ocorrenciasTotais(TPalavraProcessamento *palavra) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    return d->ocorrenciasGlobais;
}

static int numeroPaginas(TPalavraProcessamento *palavra) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    return d->numeroPaginas;
}

TDadoPalavraPreprocessamento * criarDadoPalavraPreprocessamento() {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)malloc(sizeof(TDadoPalavraPreprocessamento));
    d->paginas = criarDicionarioSemiEstatico(50, intHashing, comparaTuplaChaveInteger);
    d->numeroPaginas = 0;
    d->ocorrenciasGlobais = 0;
    return d;
}

TPalavraProcessamento * criarPalavraProcessamento() {
    TPalavraProcessamento *p = (TPalavraProcessamento*)malloc(sizeof(TPalavraProcessamento));
    p->dado = criarDadoPalavraPreprocessamento();
    p->incrementarPagina = incrementarPagina;
    p->ocorrenciasPagina = ocorrenciasPagina;
    p->ocorrenciasTotais = ocorrenciasTotais;
    p->numeroPaginas = numeroPaginas;
    return p;
}
