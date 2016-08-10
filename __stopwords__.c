#include "stopwords.h"
#include <stdio.h>

int main() {
    TStopWordManager *stop = criarStopWordManager();
    char *palavras[8] = {"ivo", "oi", "teste", "desses", "aquele", "onde", "saber", "computacao"};
    for(int i = 0; i < 8; i++) {
        printf("%s %d\n", palavras[i], stop->isStopWord(stop,palavras[i]));
    }
}
