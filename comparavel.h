typedef struct comparavel TComparavel;

typedef int (*TCompara)(void *, void *);

struct comparavel{
    void * dados;
    TCompara compara;
};
