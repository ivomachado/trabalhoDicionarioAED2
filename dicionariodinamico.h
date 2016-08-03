#define DICIONARIO_H_

typedef struct dicionario TDicionarioDinamico;

typedef void (*TInserirDicionarioDinamico)(TDicionarioDinamico*, int K, void*info);
typedef void* (*TBuscarDicionarioDinamico)(TDicionarioDinamico*, int K);
typedef void (*TAnalytiDicionarioDinamico)(TDicionarioDinamico*);
typedef int (*THashDinamico)(void *, int);

struct dicionario {
    void *dado;
    TInserirDicionarioDinamico inserir;
    TBuscarDicionarioDinamico buscar;
    TAnalytiDicionarioDinamico analytic;
};
