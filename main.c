#include "preprocessamento.h"
#include "stopwords.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

void preprocessamento(FILE *fp) {
    
}

int main(int argc, char **argv) {
    FILE *livro;
    char palavra[500];
    int pag = 0, iter = 0;
    TPreprocessamento *preprocessador;
    TStopWordManager *stop;
    if(argc < 2) {
        printf("Por favor, digite %s <caminho_relativo_livro>", argv[0]);
    } else {
        livro = fopen(argv[1], "r");
        if(livro == NULL) {
            printf("Nao foi possivel ler o arquivo %s\n", argv[1]);
        } else {
            stop = criarStopWordManager();
            preprocessador = criarPreprocessamento();
            while(lerPalavra(livro, palavra)) {
                if(strcmp(palavra,"pa") == 0) {
                    pag++;
                } else {
                    if(!stop->isStopWord(stop, palavra) && strlen(palavra) > 0) {
                        iter++;
                        preprocessador->incrementarPaginaPalavra(preprocessador, palavra, pag);
                        printf("%s: %d pag %d iter %d\n", palavra, preprocessador->ocorrenciaPaginaPalavra(preprocessador, palavra, pag), pag, iter);
                    }
                }
            }
        }
    }
    return 0;
}
