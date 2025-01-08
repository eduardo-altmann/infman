#ifndef COMPLETELEVEL_H
#define COMPLETELEVEL_H

#include "game_structs.h"

void drawCompleteLevelScreen(PLAYER *player, JOGADOR top5[], int lowerIndex, char *text);
void updateAndDrawCompleteLevelScreen(GameState *currentState, PLAYER *player, ENEMY enemies[], int *n_enemies, BLOCK blocks[], int *n_blocks, JOGADOR top5[], int lowerIndex, char *text, int *letterCount, char *fileName);
#endif