CFLAGS = -Wall -g -fms-extensions
SRC=$(wildcard *.c)
HEADERS=$(wildcard *.h)
MAIN_SRC = $(filter-out $(wildcard __*__.c), $(SRC))
NO_MAIN_SRC = $(filter-out main.c, $(MAIN_SRC))
DINAMICO_SRC = $(NO_MAIN_SRC) __dicionariodinamico__.c
SEMIESTATICO_SRC = $(NO_MAIN_SRC) __dicionariosemiestatico__.c
ESTATICO_SRC = $(NO_MAIN_SRC) __dicionarioestatico__.c
STOPWORDS_SRC = $(NO_MAIN_SRC) __stopwords__.c
a: $(HEADERS) $(MAIN_SRC) ; gcc -o $@ $^ $(CFLAGS)

dinamico: $(HEADERS) $(DINAMICO_SRC); gcc -o a $^ $(CFLAGS)
semiestatico: $(HEADERS) $(SEMIESTATICO_SRC); gcc -o a $^ $(CFLAGS)
estatico: $(HEADERS) $(ESTATICO_SRC); gcc -o a $^ $(CFLAGS)
stopword: $(HEADERS) $(STOPWORDS_SRC); gcc -o a $^ $(CFLAGS)
