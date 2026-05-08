all: jogo

jogo: main.o funcoes.o
    $(CC) -o jogo main.o funcoes.o

main.o: main.c funcoes.h personagem.h
    $(CC) -c main.c

funcoes.o: funcoes.c funcoes.h personagem.h
    $(CC) -c funcoes.c

clean:
    rm -f *.o jogo
