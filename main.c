#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "personagem.h"
#include "funcoes.h"

int main() {

    int opcao;
    Personagem jogador;

    srand(time(NULL)); // define uma semente aleatória baseada no horário atual

    while (1) {

        inicio();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            case 1:
                criar(&jogador);
                capitulo1(&jogador);
                break;

            case 2:
                le(&jogador); // carrega o personagem salvo
                capitulo1(&jogador);
                break;

            case 3:
                mostrarRankingOrdenado(); 
                break;

            case 4:
                listarIntegrantes();
                break;

            case 0:

                printf("Saindo do jogo...\n");
                return 0;

            default:
                printf("Opcao invalida!\n");
                
        }
    }
}
