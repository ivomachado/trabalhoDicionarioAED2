typedef struct lista TLista;

typedef void (*TInserirLista)(TLista*, void*);
typedef void (*TRemoverLista)(TLista*);
typedef short (*TVaziaLista)(TLista*);
typedef short (*TBuscarLista)(TLista*, void*);
typedef void (*TImprimirLista)(TLista*);

TLista* CriarLista();

struct lista {
    void *dado;
    TInserirLista inserir;
    TRemoverLista remover;
    TVaziaLista vazia;
    TBuscarLista buscar;
    TImprimirLista imprimir;
};

