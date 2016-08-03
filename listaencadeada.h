typedef struct lista TLista;

typedef void (*TInserirLista)(TLista*, void*);
typedef void (*TRemoverInicioLista)(TLista*);
typedef void (*TRemoverLista)(TLista*, void *);
typedef short (*TVaziaLista)(TLista*);
typedef short (*TBuscarLista)(TLista*, void*);
typedef void* (*TBuscarRetornoLista)(TLista*, void*);
typedef void (*TImprimirLista)(TLista*);
typedef int (*TTamanhoLista)(TLista*);

TLista* CriarLista();

struct lista {
    void *dado;
    TInserirLista inserir;
    TRemoverInicioLista removerInicio;
    TRemoverLista remover;
    TVaziaLista vazia;
    TBuscarLista buscar;
    TBuscarRetornoLista buscarComRetorno;
    TImprimirLista imprimir;
    TTamanhoLista tamanho;
};

