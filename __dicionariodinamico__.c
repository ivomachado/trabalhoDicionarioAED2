#include "dicionariodinamico.h"
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
    TDicionarioDinamico *dicionario = criarDicionarioDinamico(1, IntegerHashing, comparaTuplaChaveInteger);
    int i;
    for(i = 0; i < 100; i++) {
        a = criarInteger(i);
        dicionario->inserir(dicionario, &a->value, a);
    }

    for(i = 0; i < 100; i++) {
        a = (TInteger*)dicionario->buscar(dicionario, &i);
        a->imprimir(a);
    }
    for(i = 0; i < 100; i++) {
        dicionario->remover(dicionario, &i);
        a = (TInteger*)dicionario->buscar(dicionario, &i);
        if(a != NULL) {
            a->imprimir(a);
        }
        else {
            printf("o numero %d nao esta no dicionario mais!!\n",i);
        }
    }
}
