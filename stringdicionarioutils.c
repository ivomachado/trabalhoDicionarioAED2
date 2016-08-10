#include "tupladicionario.h"
#include "stringdicionarioutils.h"
#include <string.h>

int comparaTuplaString(void *a, void *b) {
    char *s1 = (char*)(((TTuplaDicionario*)a)->chave);
    char *s2 = (char*)(((TTuplaDicionario*)b)->chave);
    return strcmp(s1,s2);
}
