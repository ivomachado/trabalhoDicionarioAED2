#include "elemento.h"

typedef struct {
    void * chave;
    TCompara compara;
    void * valor;
}TTuplaDicionario;


typedef int (*THashing)(void*, int M);

TTuplaDicionario * criarTuplaDicionario(void * k, void * elem, TCompara compara);
