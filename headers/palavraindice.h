typedef struct palavraindice TPalavraIndice;

typedef void (*TInserirPagina)(TPalavraIndice *, int, double);
typedef void (*TImprimirPalavraIndice)(TPalavraIndice *);

TPalavraIndice * criarPalavraIndice(char * palavra, int numeroPaginas);

struct palavraindice {
    void * dado;
    TInserirPagina inserir;
    TImprimirPalavraIndice imprimir;
};
