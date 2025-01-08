#ifndef MENU_H
#define MENU_H

#include "game_structs.h"

void drawMenu();
void updateAndDrawMenu(GameState *currentState, char fileName[], BLOCK blocks[], int *n_blocks, PLAYER *player, ENEMY enemies[], int *n_enemies, char *file_name, JOGADOR top5[]);
void drawDeathScreen();
void updateDeathScreen(GameState *currentState, PLAYER *player, ENEMY enemies[], int *n_enemies, BLOCK blocks[], int *n_blocks);
void drawScoreBoard(JOGADOR top5[]);
void updateAndDrawScoreScreen(GameState *currentState, JOGADOR top5[]);


#endif