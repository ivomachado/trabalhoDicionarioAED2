#include "dicionariodinamico.h"
#include "arraydinamico.h"
#include "listaencadeada.h"
#include "tupladicionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct dado {
    int tam;
    int ocupacao;
    int fatorCarga;
    int fatorAgrupamento;
    TCompara comparaChave;
    THashing hash;
    TArrayDinamico array;
} TDadoDicionarioDinamico;

TDadoDicionarioDinamico* criarDado(int tam, double fc, THashing hash, TCompara comparaChave)
{
    TDadoDicionarioDinamico* d = (TDadoDicionarioDinamico*)malloc(sizeof(TDadoDicionarioDinamico));
    d->tam = tam * (2.0 - fc);
    d->fatorCarga = fc;
    d->fatorAgrupamento = 0.0;
    d->hash = hash;
    d->comparaChave = comparaChave;
    d->array = criarArrayDinamico(d->tam);
    d->ocupacao = 0;
    return d;
}


//TODO: implementar Evaluation
static short evaluation(TDicionario *d) {
    TDadoDicionarioDinamico *dd = d->dado;
}

static void* buscar(TDicionario* d, int k)
{
    TDadoDicionarioDinamico* dd = d->dado;

    int posi = hash(k, dd->tam);
    TLista * lista = dd->array->acessar(dd->array, posi);
    TTuplaDicionario * tupla = criarTuplaDicionario(k, NULL);
    void * elemento = lista->buscarComRetorno(lista, tupla);
    free(tupla);
    
    return elemento;
}

static void *inserir(TDicionario *d, int k, void *e)
{
    TDadoDicionarioDinamico *dd = d->dado;
    int posi = hash(k, dd->tam);
    TLista *lista = dd->array->acessar(dd->array, posi);
    TElemento elemento = (TElemento*)e;
    TTuplaDicionario *tupla = criarTuplaDicionario(k, elemento);


    if(lista == NULL) {
        lista = CriarLista();
        dd->array->atualizar(dd->array, posi, lista);
    }
    lista->inserir(lista, tupla);
    dd->ocupacao++;
}

static void *remover(TDicionario *d, int k) {
    TDadoDicionarioDinamico *dd = d->dado;
    int posi = hash(k, dd->tam);
    TLista *lista = dd->array->acessar(dd->array, posi);
    TTuplaDicionario *tupla = criarTuplaDicionario(k, NULL);
    if(lista != NULL) {
        lista->remover(lista, tupla)
    }
}

TDicionario *criarDicionarioDinamico(int tam, THashing hash, TCompara comparaChave)
{
    TDadoDicionarioDinamico* d = criarDado(tam, 0.8, hash, comparaChave);
    TDicionario *dict = malloc(sizeof(TDicionario));
    dict->buscar = buscar;
    dict->inserir = inserir;
    dict->remover = remover;
}
