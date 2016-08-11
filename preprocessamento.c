#include "preprocessamento.h"
#include "palavrapreprocessamento.h"
#include "dicionariosemiestatico.h"
#include "arraydinamico.h"
#include "primitivodicionarioutils.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    TDicionarioSemiEstatico *palavras;
    TArrayDinamico * ocorrenciasTotaisPaginas
    int totalPalavras;
    int totalPaginas;
} TDadoPreprocessamento;

static TPalavraProcessamento * getPalavraPreprocessamento(TDadoPreprocessamento * d, char * palavra) {
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

static int * getTotalOcorrenciasPagina(TDadoPreprocessamento *d, int pag)
{
    int * ocorrencias = (int*)d->ocorrenciasTotaisPaginas->acessar(d->ocorrenciasTotaisPaginas, pag - 1);
    if(ocorrencias == NULL) {
        ocorrencias = (int*)malloc(sizeof(int));
        d->ocorrenciasTotaisPaginas->atualizar(d->ocorrenciasTotaisPaginas, ocorrencias, pag - 1);
    }
    return ocorrencias;
}

static int incrementarPaginaPalavra(TPreprocessamento * p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra);
    int *totalPagina = *getTotalOcorrenciasPagina(d, pag);
    *totalPagina += 1;
    d->totalPalavras++;
    d->totalPaginas = fmax(d->totalPaginas, pag);
    return palavrapreprocessamento->incrementarPagina(palavrapreprocessamento, pag);
}

static int ocorrenciaPaginaPalavra(TPreprocessamento * p, char * palavra, int pag) {
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(p, palavra);
    return palavrapreprocessamento->ocorrenciasPagina(palavrapreprocessamento, pag);
}

static int ocorrenciaTotalPalavra(TPreprocessamento * p, char * palavra) {
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(p, palavra);
    return palavrapreprocessamento->ocorrenciasTotais(palavrapreprocessamento);
}

static float TF(TPreprocessamento *p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra);
    return palavrapreprocessamento->ocorrenciasTotais(palavrapreprocessamento)/d->totalPalavras;
}

static float IDF(TPreprocessamento *p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra);
    return log(palavrapreprocessamento->numeroPaginas(palavrapreprocessamento)/(d->totalPaginas+1));
}

static float TFIDF(TPreprocessamento *p, char * palavra, int pag) {
    return TF(p,palavra,pag)*IDF(p,palavra,pag);
}

TDadoPreprocessamento * criarDadoPreprocessamento() {
    TDadoPreprocessamento *d = (TDadoPreprocessamento *)malloc(sizeof(TDadoPreprocessamento ));
    d->palavras = criarDicionarioSemiEstatico(150, stringHashing, comparaTuplaString);
    d->totalPaginas = 0;
    d->totalPalavras = 0;
    return d;
} 

TPreprocessamento * criarPreprocessamento() {
    TPreprocessamento *p = (TPreprocessamento*)malloc(sizeof(TPreprocessamento));
    p->dado = criarDadoPreprocessamento();
    p->paginas = criarArrayDinamico(200);
    p->incrementarPaginaPalavra = incrementarPaginaPalavra;
    p->ocorrenciaPaginaPalavra = ocorrenciaPaginaPalavra;
    p->ocorrenciaTotalPalavra = ocorrenciaTotalPalavra;
    return p;
}
