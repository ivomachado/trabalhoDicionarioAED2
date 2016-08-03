#include "tupladicionario.h"
#include <stdlib.h>

TTuplaDicionario * criarTuplaDicionario(int k, void * elem, TCompara compara)
{
    TTuplaDicionario *t = malloc(sizeof(TTuplaDicionario));
    t->chave = k;
    t->valor = void;
    t->compara = compara;
    return t;
}
