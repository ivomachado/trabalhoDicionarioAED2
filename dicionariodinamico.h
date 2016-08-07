#include "tupladicionario.h"

typedef struct dicionario TDicionarioDinamico;

typedef void (*TInserirDicionarioDinamico)(TDicionarioDinamico*, void * k, void*info);
typedef void* (*TBuscarDicionarioDinamico)(TDicionarioDinamico*, void * k);
typedef void (*TRemoverDicionarioDinamico)(TDicionarioDinamico*, void * k);
typedef int (*THashDinamico)(void *, int);

TDicionarioDinamico *criarDicionarioDinamico(int tam, THashing hash, TCompara comparaTupla);

struct dicionario {
    void *dado;
    TInserirDicionarioDinamico inserir;
    TBuscarDicionarioDinamico buscar;
    TRemoverDicionarioDinamico remover;
};
