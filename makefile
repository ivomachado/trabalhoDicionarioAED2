CFLAGS = -Wall -g -fms-extensions
SRC=$(wildcard *.c)
HEADERS=$(wildcard *.h)
MAIN_SRC = $(filter-out __*__.c, $(SRC))
DINAMICO_SRC = $(filter-out main.c, $(SRC))
a: $(HEADERS) $(MAIN_SRC) ; gcc -o $@ $^ $(CFLAGS)

dinamico: $(HEADERS) $(DINAMICO_SRC); gcc -o a $^ $(CFLAGS)
