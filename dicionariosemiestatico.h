typedef struct dicionario TDicionarioSE;

typedef void (*TInserirDicionario)(TDicionarioSE*, void*, void*);
typedef void* (*TBuscarDicionario)(TDicionarioSE*, void*);
typedef void (*TAnalyticsDicionario) (TDicionarioSE*);

TDicionarioSE* criarDicioanarioSE();

struct dicionario{
    void *dado;
    TInserirDicionario inserir;
    TBuscarDicionario buscar;
    TAnalyticsDicionario analytics;
};
