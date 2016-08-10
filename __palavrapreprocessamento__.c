#include "palavrapreprocessamento.h"
#include <stdio.h>

int main() {
    TPalavraProcessamento *palavra = criarPalavraProcessamento();

    printf("%d\n", palavra->incrementarPagina(palavra, 30));
    printf("%d\n", palavra->incrementarPagina(palavra, 20));
    printf("%d\n", palavra->incrementarPagina(palavra, 20));
    printf("%d\n", palavra->ocorrenciasPagina(palavra, 30));
    printf("%d\n", palavra->ocorrenciasPagina(palavra, 20));
    printf("%d\n", palavra->ocorrenciasTotais(palavra));
}
