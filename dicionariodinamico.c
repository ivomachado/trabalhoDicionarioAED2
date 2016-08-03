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
    TArrayDinamico array;
} TDadoDicionarioDinamico;

TDadoDicionarioDinamico* criarDado(int tam, double fc)
{
    TDadoDicionarioDinamico* d = (TDadoDicionarioDinamico*)malloc(sizeof(TDadoDicionarioDinamico));
    d->tam = tam * (2.0 - fc);
    d->fatorCarga = fc;
    d->fatorAgrupamento = 0.0;
    d->array = criarArrayDinamico(d->tam);
    d->ocupacao = 0;
    return d;
}

static int hash(int k, int m)
{
    return (k % m);
}

static short evaluation(TDicionario *d) {
    TDadoDicionarioDinamico *dd = d->dado;
    int sumXi = 0;
    int amostras = sqrt(dd->tam);
    srand(time(NULL));
    do {
        int posi = rand() % dd->tam; // TODO: tem que resolver
        int i = 0;
        TComparavel *e;
        do {
            int posc = (posi + i)%dd->tam;
            i++;
            e = dd->dado[posc];
        }while(e!=NULL);
        int Xi = i - 1;
        sumXi = sumXi + Xi*Xi;
        amostras--;
    }while(amostras); // TODO: tem qeu resolverx
    double n = sqrt(dd->tam - 1);
    dd->fatorAgrupamento = (double) (sumXi)/(n - 1) - dd->fatorCarga;
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

TDicionario *criarDicionario(int tam, )
{
    TDadoDicionarioDinamico* d = criarDado(tam, 0.8);
    TDicionario *dict = malloc(sizeof(TDicionario));
    dict->buscar = buscar;
    dict->inserir = inserir;
}
