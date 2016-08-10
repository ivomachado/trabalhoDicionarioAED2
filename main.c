#include <stdio.h>

void preprocessamento(FILE *fp) {
    
}

int main(int argc, char **argv) {
    FILE *livro;
    if(argc < 2) {
        printf("Por favor, digite %s <caminho_relativo_livro>", argv[0]);
    } else {
        livro = fopen(argv[1], "r");
        if(livro == NULL) {
            printf("Nao foi possivel ler o arquivo %s\n", argv[1]);
        } else {

        }
    }
}
