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
    int rehashEnabled;
} TDadoDicionarioDinamico;

static TDadoDicionarioDinamico* criarDado(int tam, double fc, THashing hash, TCompara comparaTupla)
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
    d->rehashEnabled = 1;
    return d;
}

static void rehash(TDicionarioDinamico *dict) {
    TDadoDicionarioDinamico *d = (TDadoDicionarioDinamico*)dict->dado;
    int tam = d->tam, i;
    TArrayDinamico *old_dict = d->array, *new_dict = criarArrayDinamico(tam*d->fatorAgrupamento);
    TLista *lista;
    TTuplaDicionario *tupla;
    d->tam *= d->fatorAgrupamento;
    d->array = new_dict;
    d->ocupacao = 0;
    for(i = 0; i < tam; i++) {
        lista = (TLista*)old_dict->acessar(old_dict, i);
        if(lista != NULL) {
            while(!lista->vazia(lista)) {
                tupla = (TTuplaDicionario*)lista->removerInicio(lista);
                d->insercoesAteEvaluation++;    
                dict->inserir(dict, tupla->chave, tupla->valor);
                free(tupla);
            }
            free(lista);
        }
    }
}

static double evaluationDicionario(TDicionarioDinamico *d) {
    TDadoDicionarioDinamico *dd = d->dado;
    int groups = sqrt(dd->tam), i,j;
    double fatorAgrupamento = 0.0;
    TLista *lista;
    int posi, posc;
    for(i = 0; i < groups; i++) {
        j = 0;
        posi = rand()%groups + groups*i;
        do {
            posc = (posi+j)%(groups) + groups*i;
            j++;
            lista = (TLista*)dd->array->acessar(dd->array,posc);
        } while(lista == NULL && j < groups);
        if(lista != NULL)
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
    if(lista == NULL) return NULL;
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
        if(dd->fatorAgrupamento > 5.0 && dd->rehashEnabled) {
            dd->rehashEnabled = 0;
            rehash(d);
            evaluationDicionario(d);
            dd->rehashEnabled = 1;
        }
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
    dict->evaluation = evaluationDicionario;
    return dict;
}
