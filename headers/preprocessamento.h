
typedef struct preprocessamento TPreprocessamento;

typedef int (*TManipulacaoOcorrenciaPaginaPalavra)(TPreprocessamento*, char *, int);
typedef int (*TManipulacaoOcorrenciaTotalPalavra)(TPreprocessamento*, char*);
typedef float (*TFatorTFIDF)(TPreprocessamento *, char*, int);
typedef int (*TPreprocessamentoEstatistica)(TPreprocessamento*);
typedef char ** (*TListarPalavras)(TPreprocessamento*);

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
    TListarPalavras listarPalavras;
};
