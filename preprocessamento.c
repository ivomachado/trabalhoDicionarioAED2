#include "preprocessamento.h"
#include "palavrapreprocessamento.h"
#include "dicionariosemiestatico.h"
#include "primitivodicionarioutils.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    TDicionarioSemiEstatico *palavras;
} TDadoPreprocessamento;

static TPalavraProcessamento * getPalavraPreprocessamento(TPreprocessamento * p, char * palavra) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraProcessamento * palavrapreprocessamento = (TPalavraProcessamento*) d->palavras->buscar(d->palavras, palavra);
    char *k;
    if(palavrapreprocessamento == NULL) {
        palavrapreprocessamento = criarPalavraProcessamento();
        k = (char*)malloc(sizeof(palavra)+1);
        strcpy(k, palavra);
        d->palavras->inserir(d->palavras, k, palavrapreprocessamento);
    }
    return palavrapreprocessamento;
}


static int incrementarPaginaPalavra(TPreprocessamento * p, char * palavra, int pag) {
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(p, palavra);
    return palavrapreprocessamento->incrementarPagina(palavrapreprocessamento, pag);
}

static int decrementarPaginaPalavra(TPreprocessamento * p, char * palavra, int pag) {
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(p, palavra);
    return palavrapreprocessamento->decrementarPagina(palavrapreprocessamento, pag);
}

static int ocorrenciaPaginaPalavra(TPreprocessamento * p, char * palavra, int pag) {
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(p, palavra);
    return palavrapreprocessamento->ocorrenciasPagina(palavrapreprocessamento, pag);
}

static int ocorrenciaTotalPalavra(TPreprocessamento * p, char * palavra) {
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(p, palavra);
    return palavrapreprocessamento->ocorrenciasTotais(palavrapreprocessamento);
}

TDadoPreprocessamento * criarDadoPreprocessamento() {
    TDadoPreprocessamento *d = (TDadoPreprocessamento *)malloc(sizeof(TDadoPreprocessamento ));
    d->palavras = criarDicionarioSemiEstatico(150, stringHashing, comparaTuplaString);
    return d;
} 

TPreprocessamento * criarPreprocessamento() {
    TPreprocessamento *p = (TPreprocessamento*)malloc(sizeof(TPreprocessamento));
    p->dado = criarDadoPreprocessamento();
    p->incrementarPaginaPalavra = incrementarPaginaPalavra;
    p->decrementarPaginaPalavra = decrementarPaginaPalavra;
    p->ocorrenciaPaginaPalavra = ocorrenciaPaginaPalavra;
    p->ocorrenciaTotalPalavra = ocorrenciaTotalPalavra;
    return p;
}
