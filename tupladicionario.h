#include "elemento.h"

typedef struct {
    void * chave;
    TCompara compara;
    void * valor;
}TTuplaDicionario;


typedef int (*THashing)(void*, int M);
