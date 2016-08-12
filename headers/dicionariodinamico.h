#include "tupladicionario.h"

typedef struct dicionario TDicionarioDinamico;

typedef void (*TInserirDicionarioDinamico)(TDicionarioDinamico*, void * k, void*info);
typedef void* (*TBuscarDicionarioDinamico)(TDicionarioDinamico*, void * k);
typedef void (*TRemoverDicionarioDinamico)(TDicionarioDinamico*, void * k);
typedef double (*TEvaluationDicionario)(TDicionarioDinamico*);
typedef void (*TEstatisticaManipulacao)(TDicionarioDinamico*);
typedef int (*THashDinamico)(void *, int);

TDicionarioDinamico *criarDicionarioDinamico(int tam, int expectativaBusca, THashing hash, TCompara comparaTupla);

struct dicionario {
    void *dado;
    TInserirDicionarioDinamico inserir;
    TBuscarDicionarioDinamico buscar;
    TRemoverDicionarioDinamico remover;
    TEvaluationDicionario evaluation;
    TEstatisticaManipulacao fullEvaluation;
    TEstatisticaManipulacao enableSearchStats;
};
