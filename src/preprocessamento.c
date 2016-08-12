#include "preprocessamento.h"
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

static TPalavraPreprocessamento * getPalavraPreprocessamento(TDadoPreprocessamento * d, char * palavra, int criar) {
    TPalavraPreprocessamento * palavrapreprocessamento = (TPalavraPreprocessamento*) d->palavras->buscar(d->palavras, palavra);
    char *k;
    if(palavrapreprocessamento == NULL && criar) {
        palavrapreprocessamento = criarPalavraProcessamento();
        k = (char*)malloc(strlen(palavra)+1);
        strcpy(k, palavra);
        d->palavras->inserir(d->palavras, k, palavrapreprocessamento);
    }
    return palavrapreprocessamento;
}

static int * getTotalOcorrenciasPagina(TDadoPreprocessamento *d, int pag, int criar)
{
    int * ocorrencias = (int*)d->ocorrenciasTotaisPaginas->acessar(d->ocorrenciasTotaisPaginas, pag - 1);
    if(ocorrencias == NULL && criar) {
        ocorrencias = (int*)calloc(1, sizeof(int));
        d->ocorrenciasTotaisPaginas->atualizar(d->ocorrenciasTotaisPaginas, pag - 1, ocorrencias);
    }
    return ocorrencias;
}

static int incrementarPaginaPalavra(TPreprocessamento * p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraPreprocessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 1);
    int *totalPagina = getTotalOcorrenciasPagina(d, pag, 1);
    *totalPagina += 1;
    d->totalPaginas = fmax(d->totalPaginas, pag);
    return palavrapreprocessamento->incrementarPagina(palavrapreprocessamento, pag);
}

static int ocorrenciaPaginaPalavra(TPreprocessamento * p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraPreprocessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 0);
    if(palavrapreprocessamento != NULL)
        return palavrapreprocessamento->ocorrenciasPagina(palavrapreprocessamento, pag);
    else return 0;
}

static int ocorrenciaPagina(TPreprocessamento * p, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    int *ocorrencia = getTotalOcorrenciasPagina(d, pag, 0);
    if(ocorrencia == NULL)
        return 0;
    return *ocorrencia;
}

static int ocorrenciaTotalPalavra(TPreprocessamento * p, char * palavra) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraPreprocessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 0);
    if(palavrapreprocessamento != NULL)
        return palavrapreprocessamento->ocorrenciasTotais(palavrapreprocessamento);
    else return 0;
}

static double TF(TPreprocessamento *p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraPreprocessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 0);
    if(palavrapreprocessamento != NULL) {
        double ocorrenciasPalavra = palavrapreprocessamento->ocorrenciasPagina(palavrapreprocessamento, pag); 
        double ocorrenciasPagina = p->ocorrenciaPagina(p, pag); 
        return ocorrenciasPalavra/ocorrenciasPagina;
    }
    else return 0;
}

static double IDF(TPreprocessamento *p, char * palavra, int pag) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    TPalavraPreprocessamento *palavrapreprocessamento = getPalavraPreprocessamento(d, palavra, 0);
    double result = 0.0;
    if(palavrapreprocessamento != NULL)
        result = palavrapreprocessamento->numeroPaginas(palavrapreprocessamento)/(d->totalPaginas+1.0);
    return result;
}

static double TFIDF(TPreprocessamento *p, char * palavra, int pag) {
    double tf = TF(p,palavra,pag);
    double idf = IDF(p,palavra,pag);
    double result = tf*idf;
    return result;
}

static int totalPaginas(TPreprocessamento *p) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    return d->totalPaginas;
}

static int totalPalavras(TPreprocessamento *p) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    return d->palavras->ocupacao(d->palavras);
}

static char** listarPalavras(TPreprocessamento *p) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    return (char**)d->palavras->listarChaves(d->palavras);
}

static TPalavraPreprocessamento* buscarPalavraPreprocesssamento(TPreprocessamento* p, char * palavra) {
    TDadoPreprocessamento *d = (TDadoPreprocessamento*)p->dado;
    return d->palavras->buscar(d->palavras, palavra);
}

static TDadoPreprocessamento * criarDadoPreprocessamento() {
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
    p->ocorrenciaPagina = ocorrenciaPagina;
    p->ocorrenciaTotalPalavra = ocorrenciaTotalPalavra;
    p->totalPalavras = totalPalavras;
    p->totalPaginas = totalPaginas;
    p->listarPalavras = listarPalavras;
    p->buscarPalavraPreprocesssamento = buscarPalavraPreprocesssamento;
    p->TFIDF = TFIDF;
    p->TF = TF;
    p->IDF = IDF;
    return p;
}
