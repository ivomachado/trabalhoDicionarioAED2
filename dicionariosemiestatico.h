#include "tupladicionario.h"

typedef struct dicionario TDicionarioSemiEstatico;

typedef void (*TInserirDicionario)(TDicionarioSemiEstatico*, void*, void*);
typedef void* (*TBuscarDicionario)(TDicionarioSemiEstatico*, void*);
typedef void (*TAnalyticsDicionario) (TDicionarioSemiEstatico*);
typedef void * (*TBuscaIndice)(TDicionarioSemiEstatico*, int);

TDicionarioSemiEstatico* criarDicionarioSemiEstatico(int tam, THashing hashD, TCompara comparaTuplaD);

struct dicionario{
    void *dado;
    TInserirDicionario inserir;
    TBuscarDicionario buscar;
    TAnalyticsDicionario analytics;
    TBuscaIndice buscarIndice;
};
