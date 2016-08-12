#include "preprocessamento.h"
#include "palavraindice.h"
#include "dicionariodinamico.h"
#include "stopwords.h"
#include "primitivodicionarioutils.h"
#include "parserpalavra.h"
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *livro;
    char palavra[500];
    char *aux;
    int pag = 0, iter = 0, i;
    TDicionarioDinamico *indiceRemissivo;
    TPreprocessamento *preprocessador;
    TStopWordManager *stop;
    if(argc < 2) {
        printf("Por favor, digite %s <caminho_relativo_livro> [todas]", argv[0]);
    } else {
        livro = fopen(argv[1], "r");
        if(livro == NULL) {
            printf("Nao foi possivel ler o arquivo %s\n", argv[1]);
        } else {
            stop = criarStopWordManager();
            preprocessador = criarPreprocessamento();
            while(lerPalavra(livro, palavra)) {
                if(strcmp(palavra,"PA") == 0) {
                    pag++;
                } else {
                    aux = palavra;
                    for ( ; *aux; ++aux) *aux = tolower(*aux);
                    int isStop = stop->isStopWord(stop, palavra); 
                    if(!isStop && strlen(palavra) > 0) {
                        iter++;
                        preprocessador->incrementarPaginaPalavra(preprocessador, palavra, pag);
                    } else {
                        preprocessador->incrementarPaginaPalavra(preprocessador, "PA", pag);
                    }
                }
            }
            fclose(livro);
            int size = preprocessador->totalPalavras(preprocessador);
            char ** palavras = preprocessador->listarPalavras(preprocessador);
            TPalavraPreprocessamento *palavrapreprocessamento;
            indiceRemissivo = criarDicionarioDinamico(sqrt(size), 2, stringHashing, comparaTuplaString);
            for(i = 0; i < size; i++) {
                aux = palavras[i];
                TPalavraIndice *palavraindice = criarPalavraIndice(aux, 5);
                indiceRemissivo->inserir(indiceRemissivo, aux, palavraindice);
                palavrapreprocessamento = preprocessador->buscarPalavraPreprocesssamento(preprocessador, aux);
                int pageNumber = palavrapreprocessamento->numeroPaginas(palavrapreprocessamento);
                int ** pages = palavrapreprocessamento->listarPaginas(palavrapreprocessamento);
                for(int j = 0; j < pageNumber; j++) {
                    palavraindice->inserir(palavraindice, *pages[j], preprocessador->TFIDF(preprocessador, aux, *pages[j]));
                }
                free(pages);
            }
            TPalavraIndice *palavraindice;
            indiceRemissivo->enableSearchStats(indiceRemissivo);
            if(argc == 3 && strcmp(argv[2],"todas") == 0) {
                for(i = 0; i < size; i++) {
                    palavraindice = (TPalavraIndice*) indiceRemissivo->buscar(indiceRemissivo, palavras[i]);
                    if(palavraindice != NULL) {
                        palavraindice->imprimir(palavraindice);
                    } else {
                        printf("A palavra \"%s\" nao esta presente no indice remissivo\n", palavras[i]);
                    }
                }
            }
            else {
                printf("Digite uma palavra, digite \"pa\" para sair: ");
                scanf("%s", palavra);
                do {
                    palavraindice = (TPalavraIndice*) indiceRemissivo->buscar(indiceRemissivo, palavra);
                    if(palavraindice != NULL) {
                        palavraindice->imprimir(palavraindice);
                    } else {
                        printf("A palavra \"%s\" nao esta presente no indice remissivo\n", palavra);
                    }
                    printf("Digite uma palavra, digite \"pa\" para sair: ");
                    scanf("%s", palavra);
                } while(strcmp(palavra, "pa") != 0);
            }
            indiceRemissivo->fullEvaluation(indiceRemissivo);
        }
    }
    return 0;
}
