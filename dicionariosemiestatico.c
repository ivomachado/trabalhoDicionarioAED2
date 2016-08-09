#include "dicionariosemiestatico.h"
#include "arraydinamico.h"

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int inseriu;
    int removeu;
    int sobrecarregou;
    int movimentou;
}TAnalytics;



typedef struct {
    TArrayDinamico *dicionario; //info associada a chave, deve implementar comparavel
    TCompara comparaTupla;
    THashing hashd;
    int tamanho;
    double fatorAgrupamento;
    double fatorCarga;
    int insercoesAteEvaluation;
    TAnalytics analytics;
    short rehashEnabled;
}TDadoDicionarioSE;


static void Evaluation(TDicionarioSemiEstatico *dc){
    TDadoDicionarioSE *d = dc->dado;
    int posc, posi, i;
    TComparavel *elemento;
    float sumXi = 0, Xi;
    int n, amostras = sqrt(d->tamanho);

    srand(time(NULL));
    do{
        i = 0;
        posi = rand() % d->tamanho;
        do{
            posc = (posi+i) %d->tamanho;
            i++;
            //elemento = (TComparavel*)d->dicionario[posc];
            elemento = (TComparavel*)d->dicionario->acessar(d->dicionario, posc);
        }while(elemento != NULL);
        Xi = i-1;
        sumXi = sumXi + Xi*Xi;
        amostras--;

    }while(amostras);
    n = sqrt(d->tamanho);
    d->fatorAgrupamento = sumXi/(float)(n-1) - d->fatorCarga;
    d->insercoesAteEvaluation = rand() % 1000;
}

// static int HashDicionario(TDicionarioSemiEstatico *dc, void *k, int tam){
//     TDadoDicionarioSE *
//
//    return dc->dado->hash;
//}
static void Rehashing(TDicionarioSemiEstatico *dc){
    TDadoDicionarioSE *d = dc->dado;
    int novoTam = 2*d->tamanho*(2.0-d->fatorCarga);
    TArrayDinamico *novoDicionario = criarArrayDinamico(novoTam);
    TArrayDinamico *dic = d->dicionario;
    TTuplaDicionario *tupla;
    int i, tam = d->tamanho;

    d->dicionario = novoDicionario;
    d->tamanho = novoTam;

    d->rehashEnabled = 0;

    for(i = 0; i < tam; i++){
        tupla = (TTuplaDicionario*)dic->acessar(dic, i);
        if(tupla != NULL) {
            d->insercoesAteEvaluation++;
            dc->inserir(dc, tupla->chave, tupla->valor);
            d->analytics.movimentou++;
            free(tupla);
        }
    }
    free(dic);
    d->analytics.sobrecarregou++;
    d->rehashEnabled = 1;
}

static void Inserir(TDicionarioSemiEstatico *dc, void* k, void *elemento){
    TDadoDicionarioSE *d = dc->dado;
    int posi, posc, i = 1;
    int tentativas = d->tamanho;
    TTuplaDicionario *tupla = criarTuplaDicionario(k, elemento, d->comparaTupla);

    posi = d->hashd(k, d->tamanho);
    posc = posi;
    //while(d->dicionario[posc] != NULL && tentativas)
    while(d->dicionario->acessar(d->dicionario, posc) != NULL && tentativas){
        posc = (posi+i) % d->tamanho;
        i++;
        tentativas--;
    }
    if(tentativas == 0){
        //d->dicionario[posc] = tupla;
        Rehashing(dc);
        free(tupla);
        Evaluation(dc);
        dc->inserir(dc, k, elemento);
    } else {
        d->dicionario->atualizar(d->dicionario, posc, tupla);
        d->analytics.inseriu++;
        d->insercoesAteEvaluation--;

        if(d->insercoesAteEvaluation == 0){
            Evaluation(dc);
            if(d->fatorAgrupamento > 1.0 && d->rehashEnabled) Rehashing(dc);

        }
        
    }
}



static void* Buscar(TDicionarioSemiEstatico *dc, void* k){
    TDadoDicionarioSE *d = dc->dado;
    TComparavel *elemento = NULL;
    int posi, posc, i = 0;
    TTuplaDicionario *aux_tupla = criarTuplaDicionario(k, NULL, d->comparaTupla);

    posi = d->hashd(k, d->tamanho);
    posc = posi;

    do{

        posc = (posi+i) %d->tamanho;
        i++;
        //elemento = (TComparavel*)d->dicionario[posc];
        elemento = (TComparavel*)d->dicionario->acessar(d->dicionario, posc);

    }while(elemento != NULL && elemento->compara(elemento, aux_tupla) != 0);
    //while(elemento != NULL && elemento->compara(&(d->dicionario[posc]->dado->chave), &k) != 0);

    if(elemento != NULL)
        return ((TTuplaDicionario*)elemento)->valor;
    else return NULL;
}

static void Analytics (TDicionarioSemiEstatico *dc){
    TDadoDicionarioSE *d = dc->dado;

    printf("\nInseriu: %d", d->analytics.inseriu);
    printf("\nRemoveu: %d", d->analytics.removeu);
    printf("\nMovimentou: %d", d->analytics.movimentou);
    printf("\nSobrecarregou: %d", d->analytics.sobrecarregou);

}

static TDadoDicionarioSE* criarDadoDicionarioSE(int tam, double fc,  THashing hashD, TCompara comparaTuplaD){
    TDadoDicionarioSE *d = (TDadoDicionarioSE*)malloc(sizeof(TDadoDicionarioSE));

    srand(time(NULL));

    d->tamanho = tam*(2.0-fc);
    d->fatorCarga = fc;
    d->fatorAgrupamento = 0.0;
    d->insercoesAteEvaluation = rand() % 1000;

    d->hashd = hashD;
    d->comparaTupla = comparaTuplaD;

    d->analytics.inseriu = 0;
    d->analytics.removeu = 0;
    d->analytics.sobrecarregou = 0;
    d->analytics.movimentou = 0;
    d->rehashEnabled = 1;

    //armazena os elementos. Pode usar arraydinamico
    d->dicionario = criarArrayDinamico(d->tamanho);
    return d;

}

TDicionarioSemiEstatico* criarDicionarioSemiEstatico(int tam, THashing hashD, TCompara comparaTuplaD){
    TDicionarioSemiEstatico *dc = (TDicionarioSemiEstatico*)malloc(sizeof(TDicionarioSemiEstatico));

    dc->dado = criarDadoDicionarioSE(tam, 0.8, hashD, comparaTuplaD);

    dc->inserir = Inserir;
    dc->buscar = Buscar;
    dc->analytics = Analytics;


    return dc;
}
