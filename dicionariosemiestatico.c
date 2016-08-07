#include "dicionariosemiestatico.h"
#include "comparavel.h"
#include "arraydinamico.h"
#include "tupladicionario.h"

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
}TDadoDicionarioSE;


static void Evaluation(TDicionarioSE *dc){
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
}

// static int HashDicionario(TDicionarioSE *dc, void *k, int tam){
//     TDadoDicionarioSE *
//
//    return dc->dado->hash;
//}

static void Rehashing(TDicionarioSE *dc){
    TDadoDicionarioSE *d = dc->dado;
    int novoTam = 2*d->tamanho*(2.0-d->fatorCarga);
    TArrayDinamico *novoDicionario = criarArrayDinamico(novoTam);
    TArrayDinamico *dic = d->dicionario;
    TTuplaDicionario *tupla;
    int i = 0, tam = d->tamanho;

    free(d->dicionario);
    d->dicionario = novoDicionario;
    d->tamanho = novoTam;

    //tupla = (TTuplaDicionario*)d->dicionario->acessar(d->dicionario, i);
    tupla = (TTuplaDicionario*)dic->acessar(dic, i);

    while(i < tam){
            dc->inserir(dc, tupla->chave, tupla->valor);
            d->analytics.movimentou++;
            i++;
            tupla = (TTuplaDicionario*)dic->acessar(dic, i);
    }
    d->analytics.sobrecarregou++;

}

static void Inserir(TDicionarioSE *dc, void* k, void *elemento){
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
        //re-hashing
        //incializar os dados;
        Rehashing(dc);
    }
    //d->dicionario[posc] = tupla;
    d->dicionario->atualizar(d->dicionario, posc, tupla);
    d->analytics.inseriu++;
    d->insercoesAteEvaluation--;

    if(d->insercoesAteEvaluation == 0){
        Evaluation(dc);
        if(d->fatorAgrupamento > 1.0) Rehashing(dc);

    }
}



static void* Buscar(TDicionarioSE *dc, void* k){
    TDadoDicionarioSE *d = dc->dado;
    TComparavel *elemento = NULL;
    int posi, posc, i = 0;
    TTuplaDicionario *tupla;

    posi = d->hashd(k, d->tamanho);
    posc = posi;

    do{

        i++;
        posc = (posi+i) %d->tamanho;
        //elemento = (TComparavel*)d->dicionario[posc];
         elemento = (TComparavel*)d->dicionario->acessar(d->dicionario, posc);
         tupla = d->dicionario->acessar(d->dicionario, posc);

    }while(elemento != NULL && elemento->compara(tupla->chave, k) != 0);
    //while(elemento != NULL && elemento->compara(&(d->dicionario[posc]->dado->chave), &k) != 0);

    return elemento;
}

static void Analytics (TDicionarioSE *dc){
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

    //armazena os elementos. Pode usar arraydinamico
    d->dicionario = criarArrayDinamico(d->tamanho);
    return d;

}

TDicionarioSE* criarDicioanarioSE(int tam, THashing hashD, TCompara comparaTuplaD){
    TDicionarioSE *dc = (TDicionarioSE*)malloc(sizeof(TDicionarioSE));

    dc->dado = criarDadoDicionarioSE(tam, 0.8, hashD, comparaTuplaD);

    dc->inserir = Inserir;
    dc->buscar = Buscar;
    dc->analytics = Analytics;


    return dc;
}
