#include "palavrapreprocessamento.h"


typedef struct preprocessamento TPreprocessamento;

typedef int (*TManipulacaoOcorrenciaPaginaPalavra)(TPreprocessamento*, char *, int);
typedef int (*TManipulacaoOcorrenciaTotalPalavra)(TPreprocessamento*, char*);
typedef int (*TEstatisticaPagina)(TPreprocessamento*, int);
typedef double (*TFatorTFIDF)(TPreprocessamento *, char*, int);
typedef int (*TPreprocessamentoEstatistica)(TPreprocessamento*);
typedef char ** (*TListarPalavras)(TPreprocessamento*);


typedef TPalavraPreprocessamento* (*TBuscarPalavra)(TPreprocessamento*, char*);

TPreprocessamento * criarPreprocessamento();

struct preprocessamento {
    void * dado;
    TManipulacaoOcorrenciaPaginaPalavra incrementarPaginaPalavra;
    TManipulacaoOcorrenciaPaginaPalavra ocorrenciaPaginaPalavra;
    TManipulacaoOcorrenciaTotalPalavra ocorrenciaTotalPalavra;
    TFatorTFIDF TF;
    TFatorTFIDF IDF;
    TFatorTFIDF TFIDF;
    TPreprocessamentoEstatistica totalPalavras;
    TPreprocessamentoEstatistica totalPaginas;
    TListarPalavras listarPalavras;
    TEstatisticaPagina ocorrenciaPagina;
    TBuscarPalavra buscarPalavraPreprocesssamento;
};
