#include "dicionariodinamico.h"
#include "primitivodicionarioutils.h"
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

int main()
{
    TInteger *a;
    TDicionarioDinamico *dicionario = criarDicionarioDinamico(100, intHashing, comparaTuplaChaveInteger);
    int i;
    for(i = 0; i < 1000; i++) {
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
    system("pause");
    return 0;
}
