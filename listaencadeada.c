#include <stdlib.h>
#include "listaencadeada.h"
#include "comparavel.h"

typedef struct No TNo;

struct No{
    void *elemento;
    TNo *proximo;
};

typedef struct {
    TNo *inicio;
    TNo *fim;
}TDadoLista;

static void* CriarNo(void *elem){
    TNo *novoNo = (TNo*)malloc(sizeof(TNo));
    novoNo->elemento = elem;
    novoNo->proximo = NULL;

    return novoNo;
}

static short Vazia(TLista *l){
    TDadoLista *d = l->dado;

    if(d->inicio == NULL) return 1;

    return 0;
}

//Faz  a inser��o no fim da lista
static void inserir Inserir (TLista *l, void *elem){
    TDadoLista *d = l->dado;
    TNo *novoNo = CriarNo(elem);

    if(Vazia(l)){
        d->inicio = d->fim = novoNo;
    }
    else{
        d->fim->proximo = novoNo;
        d->fim = novoNo;
    }

}


//Remove do inicio da lista
static void RemoverInicio(TLista *l){
    TDadoLista *d = l->dado;
    TNo *no;

    if(!Vazia(l)){
        no = d->inicio;
        d->inicio = d->inicio->proximo;

        free(no);
    }
}


static void Remover(TLista *l, void * elem){
    TDadoLista *d = l->dado;
    TNo *no, *aux;
    TComparavel comp = (TComparavel*)elem;

    if(!Vazia(l)){
        aux = NULL;
        no = d->inicio;
        while(no != NULL) {
            if(comp->compara(elem, no->elemento)) {
                if(d->inicio == no) {
                    d->inicio = d->inicio->proximo;
                } else {
                    aux->proximo = no->proximo;
                }
                if(d->fim == no) {
                    d->fim = aux;
                }
                no->proximo = NULL;
            }
            aux = no;
            no = no->proximo;
        }
        free(no);
    }
}


//Diz se um elemento est� ou n�o na lista
static int Buscar(TLista *l, void *elem){
    TDadoLista *d = l->dado;
    TNo *aux;
    TComparavel *c1;


    if(Vazia(l)) return 0;

    aux = d->inicio;
    c1 = (TComparavel*)aux->elemento;
    while(aux != NULL){
        if(c1->compara(aux->elemento, elem) == 0) return 1;
        aux = aux->proximo;
    }

    return 0;
}

static void * BuscaRetorno(TLista *l, void *elem) {
    TDadoLista *d = l->dado;
    TNo *aux;
    TComparavel *c1;


    if(Vazia(l)) return 0;

    aux = d->inicio;
    c1 = (TComparavel*)aux->elemento;
    while(aux != NULL){
        if(c1->compara(aux->elemento, elem) == 0) return aux->elem;
        aux = aux->proximo;
    }

    return NULL;
}

static void Imprimir(TLista *l){
    TDadoLista *d = l->dado;
    TNo *aux;
    TComparavel *c1;

    if(!Vazia(l)){
            aux = d->inicio;
            while(aux != NULL){
                c1 = (TComparavel*)aux->elemento;
                c1->imprime(aux->elemento);
                aux = aux->proximo;
            }
    }
}

static TDadoLista* CriarDado(){
    TDadoLista *d = (TDadoLista*)malloc(sizeof(TDadoLista));

    d->inicio = d->fim = NULL;

    return d;

}


TLista* CriarLista(){
    TLista *l = (TLista*)malloc(sizeof(TLista));

    l->dado = CriarDado();
    l->inserir = Inserir;
    l->remover = Remover;
    l->removerInicio = RemoverInicio;
    l->vazia = Vazia;
    l->buscar = Buscar;
    l->imprimir = Imprimir;
    l->buscarComRetorno = BuscaRetorno;

    return l;
}
