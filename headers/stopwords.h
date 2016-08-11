
typedef struct stopwordmanager TStopWordManager;

typedef int (*TIsStopWord)(TStopWordManager *stop, char *);

TStopWordManager * criarStopWordManager();

struct stopwordmanager {
    void * dado;
    TIsStopWord isStopWord;
};
