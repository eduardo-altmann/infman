#ifndef TOP5_H
#define TOP5_H

#include "game_structs.h"

bool le_arquivo(char nome_arq[], JOGADOR top5[MAXSCORES]);

bool salva_arquivo(char nome_arq[], JOGADOR top5[MAXSCORES]);

void troca_info_array(JOGADOR top5[], JOGADOR novoj, int posicao);

void imprime_top5(JOGADOR top5[]);

void reorganizaArray(JOGADOR top5[]);

#endif
