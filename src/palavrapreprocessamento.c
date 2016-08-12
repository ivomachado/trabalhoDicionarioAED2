#include "palavrapreprocessamento.h"
#include "dicionariosemiestatico.h"
#include "primitivodicionarioutils.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    TDicionarioSemiEstatico *paginas;
    int ocorrenciasGlobais;
}TDadoPalavraPreprocessamento;

static int *getOcorrenciasPagina(TPalavraPreprocessamento *palavra, int pag, int criar) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    int *k; 
    int *ocorrencias = d->paginas->buscar(d->paginas, &pag);
    if(ocorrencias == NULL && criar) {
        k = (int*)malloc(sizeof(int));
        *k = pag;
        ocorrencias = calloc(1, sizeof(int));
        d->paginas->inserir(d->paginas, k, ocorrencias);
    }
    return ocorrencias;
}

static int incrementarPagina(TPalavraPreprocessamento *palavra, int pag) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    int *ocorrencias = getOcorrenciasPagina(palavra, pag, 1);
    *ocorrencias += 1;
    d->ocorrenciasGlobais++;
    return *ocorrencias;
}

static int ocorrenciasPagina(TPalavraPreprocessamento *palavra, int pag) {
    int * resultado = getOcorrenciasPagina(palavra, pag, 0); 
    if(resultado != NULL) return *resultado;
    else return 0;
}

static int ocorrenciasTotais(TPalavraPreprocessamento *palavra) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    return d->ocorrenciasGlobais;
}

static int numeroPaginas(TPalavraPreprocessamento *palavra) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    return d->paginas->ocupacao(d->paginas);
}

static int ** listarPaginas(TPalavraPreprocessamento *palavra) {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)palavra->dado;
    return (int**) d->paginas->listarChaves(d->paginas);
}

TDadoPalavraPreprocessamento * criarDadoPalavraPreprocessamento() {
    TDadoPalavraPreprocessamento *d = (TDadoPalavraPreprocessamento*)malloc(sizeof(TDadoPalavraPreprocessamento));
    d->paginas = criarDicionarioSemiEstatico(50, intHashing, comparaTuplaChaveInteger);
    d->ocorrenciasGlobais = 0;
    return d;
}

TPalavraPreprocessamento * criarPalavraProcessamento() {
    TPalavraPreprocessamento *p = (TPalavraPreprocessamento*)malloc(sizeof(TPalavraPreprocessamento));
    p->dado = criarDadoPalavraPreprocessamento();
    p->incrementarPagina = incrementarPagina;
    p->ocorrenciasPagina = ocorrenciasPagina;
    p->ocorrenciasTotais = ocorrenciasTotais;
    p->numeroPaginas = numeroPaginas;
    p->listarPaginas = listarPaginas;
    return p;
}
