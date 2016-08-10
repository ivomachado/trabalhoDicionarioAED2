#include "tupladicionario.h"
#include "primitivodicionarioutils.h"
#include <string.h>

int comparaTuplaString(void *a, void *b) {
    char *s1 = (char*)(((TTuplaDicionario*)a)->chave);
    char *s2 = (char*)(((TTuplaDicionario*)b)->chave);
    return strcmp(s1,s2);
}

int comparaTuplaChaveInteger(void *a, void *b)
{
    int c = *((int*)((TTuplaDicionario*)a)->chave);
    int d = *((int*)((TTuplaDicionario*)b)->chave);
    return c - d;
}

int intHashing (void *k, int m)
{
    return *((int*)k) % m;
}
