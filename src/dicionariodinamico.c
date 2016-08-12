#include "dicionariodinamico.h"
#include "arraydinamico.h"
#include "listaencadeada.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    int inseriu;
    int buscou;
    int comparou_busca;
    int rehashes;
}TAnalytics;

typedef struct dado {
    int tam;
    int ocupacao;
    int fatorCarga;
    double fatorAgrupamento;
    int insercoesAteEvaluation;
    TCompara comparaTupla;
    THashing hash;
    TArrayDinamico *array;
    int rehashEnabled;
    int searchStatsEnabled;
    int expectativaBusca;
    TAnalytics stats;
} TDadoDicionarioDinamico;

static TDadoDicionarioDinamico* criarDado(int tam, int expectativaBusca, double fc, THashing hash, TCompara comparaTupla)
{
    srand(time(NULL));
    TDadoDicionarioDinamico* d = (TDadoDicionarioDinamico*)malloc(sizeof(TDadoDicionarioDinamico));
    d->tam = tam * (2.0 - fc);
    d->fatorCarga = fc;
    d->fatorAgrupamento = 0.0;
    d->hash = hash;
    d->comparaTupla = comparaTupla;
    d->array = criarArrayDinamico(d->tam);
    d->ocupacao = 0;
    d->insercoesAteEvaluation = rand()%100;
    d->rehashEnabled = 1;
    d->searchStatsEnabled = 0;
    d->expectativaBusca = expectativaBusca;
    d->stats.inseriu = 0;
    d->stats.buscou = 0;
    d->stats.comparou_busca = 0;
    d->stats.rehashes = 0;
    return d;
}

static void rehash(TDicionarioDinamico *dict) {
    TDadoDicionarioDinamico *d = (TDadoDicionarioDinamico*)dict->dado;
    int tam = d->tam, i;
    TArrayDinamico *old_dict = d->array, *new_dict = criarArrayDinamico(tam*sqrt(d->fatorAgrupamento));
    TLista *lista;
    TTuplaDicionario *tupla;
    d->tam *= sqrt(d->fatorAgrupamento);
    d->array = new_dict;
    d->ocupacao = 0;
    d->stats.rehashes++;
    for(i = 0; i < tam; i++) {
        lista = (TLista*)old_dict->acessar(old_dict, i);
        if(lista != NULL) {
            while(!lista->vazia(lista)) {
                tupla = (TTuplaDicionario*)lista->removerInicio(lista);
                d->insercoesAteEvaluation++;
                dict->inserir(dict, tupla->chave, tupla->valor);
                free(tupla);
            }
            free(lista);
        }
    }
}

static double evaluationDicionario(TDicionarioDinamico *d) {
    TDadoDicionarioDinamico *dd = d->dado;
    int groups = sqrt(dd->tam), i,j;
    double fatorAgrupamento = 0.0;
    TLista *lista;
    int posi, posc;
    for(i = 0; i < groups; i++) {
        j = 0;
        posi = rand()%groups + groups*i;
        do {
            posc = (posi+j)%(groups) + groups*i;
            j++;
            lista = (TLista*)dd->array->acessar(dd->array,posc);
        } while(lista == NULL && j < groups);
        if(lista != NULL)
            fatorAgrupamento += pow(lista->tamanho(lista), 2);
    }
    fatorAgrupamento /= sqrt(dd->ocupacao);
    fatorAgrupamento -= dd->expectativaBusca;
    dd->fatorAgrupamento = fatorAgrupamento;
    return fatorAgrupamento;
}

static void fullEvaluation(TDicionarioDinamico *d) {
    TDadoDicionarioDinamico *dd = d->dado;
    int menor10 = 0, menorate30 = 0, menormais30 = 0;
    int maior10 = 0, maiorate30 = 0, maiormais30 = 0;
    int igualfator = 0;
    int vazios = 0;
    double rate;
    TLista *l;
    d->evaluation(d);
    for(int i = 0; i < dd->tam; i++) {
        l = (TLista*)dd->array->acessar(dd->array, i);
        if(l != NULL) {
            rate = ((double)l->tamanho(l))/dd->expectativaBusca;
            if(rate > 1.3) maiormais30++;
            else if(rate > 1.1 && rate <= 1.3) maiorate30++;
            else if (rate > 1.0 && rate < 1.1) maior10++;
            else if(rate < 0.7) menormais30++;
            else if(rate < 0.9 && rate >= 0.7) menorate30++;
            else if (rate < 1.0 && rate > 0.9) menor10++;
            else igualfator++;
        } else vazios++;
    }
    printf("A tabela tem tamanho %d\n", dd->tam);
    printf("%.2f porcento tem ocupacao ate 10 porcento maior que o fator de carga\n", (maior10*100.0)/dd->tam);
    printf("%.2f porcento tem ocupacao ate 30 porcento maior que o fator de carga\n", (maiorate30*100.0)/dd->tam);
    printf("%.2f porcento tem ocupacao maior que 30 porcento do fator de carga\n", (maiormais30*100.0)/dd->tam);
    printf("%.2f porcento tem ocupacao igual ao fator de carga\n", (igualfator*100.0)/dd->tam);
    printf("%.2f porcento tem ocupacao ate 10 porcento menor que o fator de carga\n", (menor10*100.0)/dd->tam);
    printf("%.2f porcento tem ocupacao ate 30 porcento menor que o fator de carga\n", (menorate30*100.0)/dd->tam);
    printf("%.2f porcento tem ocupacao menor que 30 porcento do fator de carga\n", (menormais30*100.0)/dd->tam);
    printf("%.2f porcento da tabela esta ocupada\n",  100.0 - vazios*100.0/dd->tam);

    printf("%d buscas foram feitas com um total de %d comparacoes\n", dd->stats.buscou, dd->stats.comparou_busca);
    printf("%d rehashes foram feitos\n", dd->stats.rehashes);

    printf("O fator de agrupamento e %.4f\n",dd->fatorAgrupamento);
}

static void enableSearchStats(TDicionarioDinamico* p) {
    TDadoDicionarioDinamico *dd = p->dado;
    dd->searchStatsEnabled = 1;
}

static void* buscar(TDicionarioDinamico* d, void * k)
{
    TDadoDicionarioDinamico* dd = d->dado;

    int posi = dd->hash(k, dd->tam), iter;
    TLista * lista = dd->array->acessar(dd->array, posi);
    if(lista == NULL) return NULL;
    TTuplaDicionario * tupla = criarTuplaDicionario(k, NULL, dd->comparaTupla);
    TTuplaDicionario * elemento = (TTuplaDicionario*) lista->buscarComRetorno(lista, tupla, &iter);
    if(dd->searchStatsEnabled) {
        printf("foram feitas %d comparacoes para esta busca, ", iter);
        dd->stats.buscou++;
        dd->stats.comparou_busca += iter;
    }
    free(tupla);
    if(elemento == NULL) return NULL;
    return elemento->valor;
}

static void inserir(TDicionarioDinamico *d, void * k, void *e)
{
    TDadoDicionarioDinamico *dd = d->dado;
    int posi = dd->hash(k, dd->tam);
    TLista *lista = dd->array->acessar(dd->array, posi);
    TElemento *elemento = (TElemento*)e;
    TTuplaDicionario *tupla = criarTuplaDicionario(k, elemento, dd->comparaTupla);


    if(lista == NULL) {
        lista = CriarLista();
        dd->array->atualizar(dd->array, posi, lista);
    }
    lista->inserir(lista, tupla);
    dd->ocupacao++;
    dd->stats.inseriu++;
    dd->insercoesAteEvaluation--;
    if(dd->insercoesAteEvaluation == 0) {
        dd->insercoesAteEvaluation = rand()%100;
        evaluationDicionario(d);
        if(dd->fatorAgrupamento > 2.0 && dd->rehashEnabled) {
            dd->rehashEnabled = 0;
            rehash(d);
            evaluationDicionario(d);
            dd->rehashEnabled = 1;
        }
    }
}

static void remover(TDicionarioDinamico *d, void * k) {
    TDadoDicionarioDinamico *dd = d->dado;
    int posi = dd->hash(k, dd->tam);
    TLista *lista = dd->array->acessar(dd->array, posi);
    TTuplaDicionario *tupla = criarTuplaDicionario(k, NULL, dd->comparaTupla);
    if(lista != NULL) {
        lista->remover(lista, tupla);
    }
}

TDicionarioDinamico *criarDicionarioDinamico(int tam, int expectativaBusca, THashing hash, TCompara comparaTupla)
{
    TDadoDicionarioDinamico* d = criarDado(tam, expectativaBusca, 0.8, hash, comparaTupla);
    TDicionarioDinamico *dict = malloc(sizeof(TDicionarioDinamico));
    dict->dado = d;
    dict->buscar = buscar;
    dict->inserir = inserir;
    dict->remover = remover;
    dict->evaluation = evaluationDicionario;
    dict->fullEvaluation = fullEvaluation;
    dict->enableSearchStats = enableSearchStats;
    return dict;
}
