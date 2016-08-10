#include "primitivodicionarioutils.h"
#include "tupladicionario.h"
#include <string.h>

int comparaTuplaString(void* a, void* b)
{
    char* s1 = (char*)(((TTuplaDicionario*)a)->chave);
    char* s2 = (char*)(((TTuplaDicionario*)b)->chave);
    return strcmp(s1, s2);
}

int comparaTuplaChaveInteger(void* a, void* b)
{
    int c = *((int*)((TTuplaDicionario*)a)->chave);
    int d = *((int*)((TTuplaDicionario*)b)->chave);
    return c - d;
}

int intHashing(void* k, int m)
{
    return *((int*)k) % m;
}

int stringHashing(void * k, int m)
{
    char* str = (char*)k;
    int len = strlen(str);
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++) {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0) {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return intHashing(&hash, m);
}
