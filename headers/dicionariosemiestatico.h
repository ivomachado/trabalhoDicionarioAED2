#include "tupladicionario.h"

typedef struct dicionario TDicionarioSemiEstatico;

typedef void (*TInserirDicionario)(TDicionarioSemiEstatico*, void*, void*);
typedef void* (*TBuscarDicionario)(TDicionarioSemiEstatico*, void*);
typedef void (*TAnalyticsDicionario) (TDicionarioSemiEstatico*);
typedef void ** (*TListarChavesDicionarioSemiEstatico)(TDicionarioSemiEstatico*);
typedef int (*TOcupacaoDicionarioSemiEstatico)(TDicionarioSemiEstatico*);

TDicionarioSemiEstatico* criarDicionarioSemiEstatico(int tam, THashing hashD, TCompara comparaTuplaD);

struct dicionario{
    void *dado;
    TInserirDicionario inserir;
    TBuscarDicionario buscar;
    TAnalyticsDicionario analytics;
    TListarChavesDicionarioSemiEstatico listarChaves;
    TOcupacaoDicionarioSemiEstatico ocupacao;
};
