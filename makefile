CFLAGS = -Wall -g -fms-extensions -std=c99 -lm
INCLUDE = -Iheaders
SRC=$(wildcard src/*.c)
HEADERS=$(wildcard headers/*.h)
MAIN_SRC = $(SRC) main.c
DINAMICO_SRC = $(SRC) tests/__dicionariodinamico__.c
SEMIESTATICO_SRC = $(SRC) tests/__dicionariosemiestatico__.c
ESTATICO_SRC = $(SRC) tests/__dicionarioestatico__.c
STOPWORDS_SRC = $(SRC) tests/__stopwords__.c
PALAVRAPREPROCESSAMENTO_SRC = $(SRC) tests/__palavrapreprocessamento__.c

a: $(HEADERS) $(MAIN_SRC) ; gcc $(INCLUDE) -o $@ $^ $(CFLAGS)
dinamico:  $(HEADERS) $(DINAMICO_SRC); gcc $(INCLUDE) -o a $^ $(CFLAGS)
semiestatico:  $(HEADERS) $(SEMIESTATICO_SRC); gcc $(INCLUDE) -o a $^ $(CFLAGS)
estatico:  $(HEADERS) $(ESTATICO_SRC); gcc $(INCLUDE) -o a $^ $(CFLAGS)
stopword:  $(HEADERS) $(STOPWORDS_SRC); gcc $(INCLUDE) -o a $^ $(CFLAGS)
palavrapreprocessamento: $(HEADERS) $(PALAVRAPREPROCESSAMENTO_SRC); gcc $(INCLUDE) -o a $^ $(CFLAGS)
