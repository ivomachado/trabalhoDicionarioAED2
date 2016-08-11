#include "arraydinamico.h"
#include <math.h>
#include <stdlib.h>

typedef struct{
	void **_dado;
	int tamanho;
} TDado;

static void** ajustar(void *_add, int novoTamanho){
	TDado *d=_add;
	void **novo = calloc(novoTamanho,sizeof(void*));
	int i;
	for (i=0;i< d->tamanho;i++)
        novo[i] = d->_dado[i];
	free(d->_dado);
	return novo;
}
static void* acessar(TArrayDinamico* ad, int pos){
	TDado *dado = ad->dado;
	if(pos >= 0 && pos < dado->tamanho)
		return dado->_dado[pos];
	return NULL;
}
static void atualizar(TArrayDinamico* ad, int pos, void* elemento){
	TDado *d = ad->dado;
	int k, novoTamanho;
	if (pos >= d->tamanho){
		k = floor(log2(pos)) + 1;
		novoTamanho = (int)pow(2,k);
		d->_dado = ajustar(d, novoTamanho);
		d->tamanho = novoTamanho;
	}
	d->_dado[pos] = elemento;
}
static int tamanho(TArrayDinamico *ad){
	TDado *d = ad->dado;
	return d->tamanho;
}
static void *criarDado(int tam){
	TDado *d = malloc(sizeof(TDado));
	d->tamanho=tam;
	d->_dado = calloc(d->tamanho, sizeof(void*));
	return d;
}

TArrayDinamico* criarArrayDinamico(int tam){
	TArrayDinamico *ad = malloc(sizeof(TArrayDinamico));
	ad->dado = criarDado(tam);
	ad->acessar = acessar;
	ad->atualizar = atualizar;
	ad->tamanho = tamanho;
	return ad;
}
