#ifndef STATEHANDLERS_H
#define STATEHANDLERS_H

#include "game_structs.h"

void loopUpdates(PLAYER *player, BLOCK blocks[], int *n_blocks, ENEMY enemies[], int *n_enemies, GameState *currentState, Camera2D *camera);
void gameDrawUpdates(PLAYER *player, Camera2D *camera, BACKGROUND *bg, ENEMY enemies[], int *n_enemies, BLOCK blocks[], int *n_blocks);
void resetGameState(PLAYER *player, ENEMY enemies[], int *n_enemies, BLOCK blocks[], int *n_blocks);

#endif
