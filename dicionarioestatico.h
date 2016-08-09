#include "tupladicionario.h"

typedef struct dicionarioEstatico TDicionarioEstatico;

typedef void* (*TBuscarDicionarioEstatico)(TDicionarioEstatico*, void * K);

TDicionarioEstatico * criarDicionarioEstatico(void ** dataArray, void** keyArray, int size, TCompara comparaTupla);
 
struct dicionarioEstatico {
    void *dado;
    TBuscarDicionarioEstatico buscar;
};
