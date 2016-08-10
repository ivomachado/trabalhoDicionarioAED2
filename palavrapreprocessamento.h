typedef struct palavraprocessamento TPalavraProcessamento;

typedef int (*TOcorrenciasTotal)(TPalavraProcessamento*);
typedef int (*TManipulacaoOcorrencia)(TPalavraProcessamento*, int);


struct palavraprocessamento {
    void * dado;
    TManipulacaoOcorrencia incrementarPagina;
    TManipulacaoOcorrencia decrementarPagina;
    TManipulacaoOcorrencia ocorrenciasPagina;
    TOcorrenciasTotal ocorrenciasTotais;
};
