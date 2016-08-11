#include "dicionariodinamico.h"
#include "arraydinamico.h"
#include "listaencadeada.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct dado {
    int tam;
    int ocupacao;
    int fatorCarga;
    int fatorAgrupamento;
    int insercoesAteEvaluation;
    TCompara comparaTupla;
    THashing hash;
    TArrayDinamico *array;
} TDadoDicionarioDinamico;

TDadoDicionarioDinamico* criarDado(int tam, double fc, THashing hash, TCompara comparaTupla)
{
    srand(time(NULL));
    TDadoDicionarioDinamico* d = (TDadoDicionarioDinamico*)malloc(sizeof(TDadoDicionarioDinamico));
    d->tam = tam * (2.0 - fc);
    d->fatorCarga = fc;
    d->fatorAgrupamento = 0.0;
    d->hash = hash;
    d->comparaTupla = comparaTupla;
    d->array = criarArrayDinamico(d->tam);
    d->ocupacao = 0;
    d->insercoesAteEvaluation = rand()%100;
    return d;
}

static double evaluationDicionario(TDicionarioDinamico *d) {
    TDadoDicionarioDinamico *dd = d->dado;
    int groups = sqrt(dd->tam), i,j;
    double fatorAgrupamento = 0.0;
    TLista *lista;
    int pos;
    for(i = 0; i < groups; i++) {
        j = 0;
        do {
            pos = rand()%groups + groups*i + j;
            pos = pos%groups*(i+1);
            j++;
            lista = (TLista*)dd->array->acessar(dd->array,pos);
        } while(lista == NULL);
        fatorAgrupamento += lista->tamanho(lista);
    }
    fatorAgrupamento /= groups;
    fatorAgrupamento -= dd->fatorCarga;
    dd->fatorAgrupamento = fatorAgrupamento;
    return fatorAgrupamento;
}

static void* buscar(TDicionarioDinamico* d, void * k)
{
    TDadoDicionarioDinamico* dd = d->dado;

    int posi = dd->hash(k, dd->tam);
    TLista * lista = dd->array->acessar(dd->array, posi);
    TTuplaDicionario * tupla = criarTuplaDicionario(k, NULL, dd->comparaTupla);
    TTuplaDicionario * elemento = (TTuplaDicionario*) lista->buscarComRetorno(lista, tupla);
    free(tupla);
    if(elemento == NULL) return NULL;
    return elemento->valor;
}

static void inserir(TDicionarioDinamico *d, void * k, void *e)
{
    TDadoDicionarioDinamico *dd = d->dado;
    int posi = dd->hash(k, dd->tam);
    TLista *lista = dd->array->acessar(dd->array, posi);
    TElemento *elemento = (TElemento*)e;
    TTuplaDicionario *tupla = criarTuplaDicionario(k, elemento, dd->comparaTupla);


    if(lista == NULL) {
        lista = CriarLista();
        dd->array->atualizar(dd->array, posi, lista);
    }
    lista->inserir(lista, tupla);
    dd->ocupacao++;
    dd->insercoesAteEvaluation--;
    if(dd->insercoesAteEvaluation == 0) {
        dd->insercoesAteEvaluation = rand()%100;
        evaluationDicionario(d);
        // TODO : fazer rehash
    }
}

static void remover(TDicionarioDinamico *d, void * k) {
    TDadoDicionarioDinamico *dd = d->dado;
    int posi = dd->hash(k, dd->tam);
    TLista *lista = dd->array->acessar(dd->array, posi);
    TTuplaDicionario *tupla = criarTuplaDicionario(k, NULL, dd->comparaTupla);
    if(lista != NULL) {
        lista->remover(lista, tupla);
    }
}

TDicionarioDinamico *criarDicionarioDinamico(int tam, THashing hash, TCompara comparaTupla)
{
    TDadoDicionarioDinamico* d = criarDado(tam, 0.8, hash, comparaTupla);
    TDicionarioDinamico *dict = malloc(sizeof(TDicionarioDinamico));
    dict->dado = d;
    dict->buscar = buscar;
    dict->inserir = inserir;
    dict->remover = remover;
    return dict;
}
