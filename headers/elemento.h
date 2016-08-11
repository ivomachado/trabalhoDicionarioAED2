#include "comparavel.h"

typedef void (*TImprimir)(void *);

typedef struct {
    struct comparavel;
    TImprimir imprimir; 
}TElemento;
