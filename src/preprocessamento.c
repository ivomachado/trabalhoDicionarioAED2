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
    TArrayDinamico * ocorrenciasTotaisPaginas;
    int totalPaginas;
} TDadoPreprocessamento;

static TPalavraProcessamento * getPalavraPreprocessamento(TDadoPreprocessamento * d, char * palavra, int criar) {
    TPalavraProcessamento * palavrapreprocessamento = (TPalavraProcessamento*) d->palavras->buscar(d->palavras, palavra);
    char *k;
    if(palavrapreprocessamento == NULL && criar) {
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
        d->ocorrenciasTotaisPaginas->atualizar(d->ocorrenciasTotaisPaginas, pag - 1, ocorrencias);
    }
    return ocorrencias;
}

static int incrementarPaginaPalavra(TPreprocessamento * p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 1);
    int *totalPagina = getTotalOcorrenciasPagina(d, pag);
    *totalPagina += 1;
    d->totalPaginas = fmax(d->totalPaginas, pag);
    return palavrapreprocessamento->incrementarPagina(palavrapreprocessamento, pag);
}

static int ocorrenciaPaginaPalavra(TPreprocessamento * p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 0);
    if(palavrapreprocessamento != NULL)
        return palavrapreprocessamento->ocorrenciasPagina(palavrapreprocessamento, pag);
    else return 0;
}

static int ocorrenciaTotalPalavra(TPreprocessamento * p, char * palavra) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 0);
    if(palavrapreprocessamento != NULL)
        return palavrapreprocessamento->ocorrenciasTotais(palavrapreprocessamento);
    else return 0;
}

static float TF(TPreprocessamento *p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 0);
    if(palavrapreprocessamento != NULL)
        return palavrapreprocessamento->ocorrenciasTotais(palavrapreprocessamento)/d->palavras->ocupacao(d->palavras);
    else return 0;
}

static float IDF(TPreprocessamento *p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraProcessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 0);
    if(palavrapreprocessamento != NULL)
        return log(palavrapreprocessamento->numeroPaginas(palavrapreprocessamento)/(d->totalPaginas+1));
    else return 0;
}

static float TFIDF(TPreprocessamento *p, char * palavra, int pag) {
    return TF(p,palavra,pag)*IDF(p,palavra,pag);
}

static int totalPalavras(TPreprocessamento *p) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    return d->palavras->ocupacao(d->palavras);
}

static char** listarPalavras(TPreprocessamento *p) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    return (char**)d->palavras->listarChaves(d->palavras);
}

TDadoPreprocessamento * criarDadoPreprocessamento() {
    TDadoPreprocessamento *d = (TDadoPreprocessamento *)malloc(sizeof(TDadoPreprocessamento ));
    d->palavras = criarDicionarioSemiEstatico(150, stringHashing, comparaTuplaString);
    d->totalPaginas = 0;
    d->ocorrenciasTotaisPaginas = criarArrayDinamico(200);
    return d;
}

TPreprocessamento * criarPreprocessamento() {
    TPreprocessamento *p = (TPreprocessamento*)malloc(sizeof(TPreprocessamento));
    p->dado = criarDadoPreprocessamento();
    p->incrementarPaginaPalavra = incrementarPaginaPalavra;
    p->ocorrenciaPaginaPalavra = ocorrenciaPaginaPalavra;
    p->ocorrenciaTotalPalavra = ocorrenciaTotalPalavra;
    p->totalPalavras = totalPalavras;
    p->listarPalavras = listarPalavras;
    p->TFIDF = TFIDF;
    p->TF = TF;
    p->IDF = IDF;
    return p;
}
