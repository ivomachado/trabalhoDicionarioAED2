typedef struct palavraprocessamento TPalavraProcessamento;

typedef int (*TOcorrenciasTotal)(TPalavraProcessamento*);
typedef int (*TManipulacaoOcorrencia)(TPalavraProcessamento*, int);
typedef int** (*TListarPaginas)(TPalavraProcessamento*);

TPalavraProcessamento * criarPalavraProcessamento();

struct palavraprocessamento {
    void * dado;
    TManipulacaoOcorrencia incrementarPagina;
    TManipulacaoOcorrencia ocorrenciasPagina;
    TOcorrenciasTotal ocorrenciasTotais;
    TOcorrenciasTotal numeroPaginas;
    TListarPaginas listarPaginas;
};
