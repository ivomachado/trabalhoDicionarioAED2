#include "palavraindice.h"
#include "arraydinamico.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int pag;
    double tfidf;
} TPaginaIndice;

typedef struct {
    TArrayDinamico *paginas;
    int numeroPaginas;
    int inseridas;
    char * palavra;
}TDadoPalavraIndice;


static TPaginaIndice * criarPaginaIndice(int pag, double tfidf) {
    TPaginaIndice *pagina = (TPaginaIndice*)malloc(sizeof(TPaginaIndice));
    pagina->tfidf = tfidf;
    pagina->pag = pag;
    return pagina;
}

static void inserir(TPalavraIndice* p, int pag, double tfidf) {
    TDadoPalavraIndice *d = (TDadoPalavraIndice*)p->dado;
    int i = d->numeroPaginas - 1;
    TPaginaIndice *aux = (TPaginaIndice*)d->paginas->acessar(d->paginas, i), *pagina;
    if(tfidf > aux->tfidf) {
        i--;
        free(aux);
        if(d->inseridas < d->numeroPaginas)
            d->inseridas++;
        pagina = criarPaginaIndice(pag, tfidf);
        aux = (TPaginaIndice*)d->paginas->acessar(d->paginas, i);
        while(i >= 0 && tfidf > aux->tfidf) {
            d->paginas->atualizar(d->paginas, i + 1, aux);
            i--;
            aux = (TPaginaIndice*)d->paginas->acessar(d->paginas, i);
        }
        d->paginas->atualizar(d->paginas, i + 1, pagina);
    }
}

static void imprimir(TPalavraIndice* p) {
    TDadoPalavraIndice *d = (TDadoPalavraIndice*)p->dado;
    TPaginaIndice *pagina;
    printf("Paginas de maior relevancia: ");
    for(int i = 0; i < d->inseridas; i++) {
        pagina = (TPaginaIndice*)d->paginas->acessar(d->paginas, i);
        printf("%d ", pagina->pag);
    }
    printf("\n");
}

static TDadoPalavraIndice * criarDadoPalavraIndice(char * palavra,int numeroPaginas) {
    TDadoPalavraIndice *d = (TDadoPalavraIndice*)malloc(sizeof(TDadoPalavraIndice));
    d->paginas = criarArrayDinamico(numeroPaginas);
    d->inseridas = 0;
    d->palavra = (char*)malloc(sizeof(char)*(strlen(palavra)+1));
    strcpy(d->palavra, palavra);
    d->numeroPaginas = numeroPaginas > 0? numeroPaginas : 1;
    for(int i = 0; i < numeroPaginas; i++) {
        d->paginas->atualizar(d->paginas, i, criarPaginaIndice(0, 0));
    }
    return d;
}

TPalavraIndice * criarPalavraIndice(char * palavra, int numeroPaginas) {
    TPalavraIndice *p = (TPalavraIndice*)malloc(sizeof(TPalavraIndice));
    p->dado = criarDadoPalavraIndice(palavra, numeroPaginas);

    p->inserir = inserir;
    p->imprimir = imprimir;
    return p;
}
