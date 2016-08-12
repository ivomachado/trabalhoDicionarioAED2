#include "palavrapreprocessamento.h"
#include <stdio.h>

int main() {
    TPalavraProcessamento *palavra = criarPalavraProcessamento();

    printf("%d\n", palavra->incrementarPagina(palavra, 30));
    printf("%d\n", palavra->incrementarPagina(palavra, 20));
    printf("%d\n", palavra->incrementarPagina(palavra, 20));
    printf("%d\n", palavra->ocorrenciasPagina(palavra, 30));
    printf("%d\n", palavra->ocorrenciasPagina(palavra, 20));
    int size = palavra->numeroPaginas(palavra);
    int ** array = palavra->listarPaginas(palavra);
    for(int i = 0; i < size; i++) {
        printf("pagina %d\n", *array[i]);
    }
    printf("%d\n", palavra->ocorrenciasTotais(palavra));
}
