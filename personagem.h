#ifndef PERSONAGEM_H
#define PERSONAGEM_H

typedef struct { 

    char nome[50];
    char amada[50];
    char local[50];
    int pontuacao;
    char alinhamento[10];
    int alinhamento_cont;
    int forca, inteligencia, sabedoria, carisma;
    int vida, magia, energia;
    int itens[10];
    int quests[10];
    
} Personagem;

#endif
