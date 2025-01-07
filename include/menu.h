#ifndef MENU_H
#define MENU_H

#include "game_structs.h"

void drawMenu();
void updateAndDrawMenu(GameState *currentState);
void drawDeathScreen();
void updateDeathScreen(GameState *currentState);

#endif