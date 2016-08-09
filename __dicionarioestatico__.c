#include "dicionarioestatico.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct integer TInteger;

struct integer {
    int value;
    TCompara compara;
    TImprimir imprimir;
};

static int comparaInteger(void *a, void *b)
{
    return ((TInteger*)a)->value - ((TInteger*)b)->value;
}

static void imprimirInteger(void *a)
{
    printf("%d\n", ((TInteger*)a)->value);
}

TInteger * criarInteger(int value)
{
    TInteger *a = (TInteger*)malloc(sizeof(TInteger));
    a->value = value;
    a->imprimir = imprimirInteger;
    a->compara = comparaInteger;
    return a;
}

static int comparaTuplaChaveInteger(void *a, void *b)
{
    int c = *((int*)((TTuplaDicionario*)a)->chave);
    int d = *((int*)((TTuplaDicionario*)b)->chave);
    return c - d;
}

static int IntegerHashing (void *k, int m)
{
    return *((int*)k) % m;
}

int main()
{
    TInteger *a;
    TInteger *array[1000];
    int *keys[1000], *key;
    TDicionarioEstatico *dicionario;
    int i;
    for(i = 0; i < 1000; i++) {
        array[i] = criarInteger(i);
        key = (int*)malloc(sizeof(int)); *key = i;
        keys[i] = key;
    }
    dicionario = criarDicionarioEstatico((void**)keys, (void**)array, 1000, comparaTuplaChaveInteger);
    for(i = 0; i < 1000; i++) {
        a = (TInteger*)dicionario->buscar(dicionario, &i);
        a->imprimir(a);
    }
    system("pause");
    return 0;
}
