typedef struct palavraprocessamento TPalavraPreprocessamento;

typedef int (*TOcorrenciasTotal)(TPalavraPreprocessamento*);
typedef int (*TManipulacaoOcorrencia)(TPalavraPreprocessamento*, int);
typedef int** (*TListarPaginas)(TPalavraPreprocessamento*);

TPalavraPreprocessamento * criarPalavraProcessamento();

struct palavraprocessamento {
    void * dado;
    TManipulacaoOcorrencia incrementarPagina;
    TManipulacaoOcorrencia ocorrenciasPagina;
    TOcorrenciasTotal ocorrenciasTotais;
    TOcorrenciasTotal numeroPaginas;
    TListarPaginas listarPaginas;
};
