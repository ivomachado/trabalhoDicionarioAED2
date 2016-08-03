#include "tupladicionario.h"
#include <stdlib.h>

TTuplaDicionario * criarTuplaDicionario(int k, TElemento * elem, TCompara compara)
{
    TTuplaDicionario *t = malloc(sizeof(TTuplaDicionario));
    t->chave = k;
    t->valor = elem;
    t->compara = compara;
    return t;
}
