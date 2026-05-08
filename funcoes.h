#ifndef FUNCOES_H // verifica se a funcoes_h já foi definida em algum lugar
#define FUNCOES_H // se nao foi, agora ela será

#include "personagem.h"

void inicio();
void criar(Personagem *p);
void grava(Personagem p);
void le(Personagem *p);
void mostrarRanking();
void mostrarRankingOrdenado();
void listarIntegrantes();
void combate(Personagem *jogador, Personagem *inimigo);
void atualizarAlinhamento(Personagem *p);
void capitulo1(Personagem *p);
void capitulo2(Personagem *p);
void capitulo3(Personagem *p);
void capituloFinal(Personagem *p);
void final();
void recorde(Personagem p);

#endif // Fecha o bloco do ifndef
