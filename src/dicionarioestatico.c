#include "dicionarioestatico.h"
#include "arraydinamico.h"
#include <stdlib.h>

typedef struct {
    int tam;
    TArrayDinamico *array;
    TCompara comparaTupla;
}TDadoDicionarioEstatico;

static void * buscar(TDicionarioEstatico *dict, void *k) {
    TDadoDicionarioEstatico *d = (TDadoDicionarioEstatico*)dict->dado;
    int ini = 0, fim = d->tam - 1;
    int meio, resultadoComparacao;
    TTuplaDicionario *comp;
    TTuplaDicionario *tupla = criarTuplaDicionario(k, NULL, d->comparaTupla);
    do {
        meio = (ini + fim)/2;
        comp = (TTuplaDicionario*)d->array->acessar(d->array, meio);
        resultadoComparacao = tupla->compara(tupla, comp);
        if(resultadoComparacao < 0) {
            fim = meio - 1;
        } else {
            if(resultadoComparacao > 0) {
                ini = meio + 1;
            }
            else {
                if(resultadoComparacao == 0) {
                    return comp->valor;
                }
            }
        }
    }while(ini <= fim);
    return NULL;
}

TDadoDicionarioEstatico * criarDadoDicionarioEstatico(void ** keyArray, void** dataArray, int size, TCompara comparaTupla) {
    TDadoDicionarioEstatico * dado = malloc(sizeof(TDadoDicionarioEstatico));
    dado->array = criarArrayDinamico(size);
    for(int i = 0; i < size; i++) {
        dado->array->atualizar(dado->array, i, criarTuplaDicionario(keyArray[i], dataArray[i], comparaTupla));
    }
    dado->comparaTupla = comparaTupla;
    dado->tam = size;
    return dado;
}

TDicionarioEstatico * criarDicionarioEstatico(void ** dataArray, void** keyArray, int size, TCompara comparaTupla)
{
    TDicionarioEstatico *dict = malloc(sizeof(TDicionarioEstatico));
    dict->dado = criarDadoDicionarioEstatico(dataArray, keyArray, size, comparaTupla);
    dict->buscar = buscar;
    return dict;
}

