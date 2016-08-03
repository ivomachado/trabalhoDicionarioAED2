#include "elemento.h"

typedef struct {
    void * chave;
    TCompara compara;
    TElemento *valor;
}TTuplaDicionario;
