
typedef struct preprocessamento TPreprocessamento;

typedef int (*TManipulacaoOcorrenciaPaginaPalavra)(TPreprocessamento*, char *, int);
typedef int (*TManipulacaoOcorrenciaTotalPalavra)(TPreprocessamento*, char*);

TPreprocessamento * criarPreprocessamento();

struct preprocessamento {
    void * dado;
    TManipulacaoOcorrenciaPaginaPalavra incrementarPaginaPalavra;
    TManipulacaoOcorrenciaPaginaPalavra decrementarPaginaPalavra;
    TManipulacaoOcorrenciaPaginaPalavra ocorrenciaPaginaPalavra;
    TManipulacaoOcorrenciaTotalPalavra ocorrenciaTotalPalavra;
};
