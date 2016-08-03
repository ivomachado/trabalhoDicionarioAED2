typedef struct dicionario TDicionarioDinamico;

typedef void (*TInserirDicionarioDinamico)(TDicionarioDinamico*, int K, void*info);
typedef void* (*TBuscarDicionarioDinamico)(TDicionarioDinamico*, int K);
typedef void* (*TRemoverDicionarioDinamico)(TDicionarioDinamico*, int K);
typedef int (*THashDinamico)(void *, int);

struct dicionario {
    void *dado;
    TInserirDicionarioDinamico inserir;
    TBuscarDicionarioDinamico buscar;
    TRemoverDicionarioDinamico remover;
};
