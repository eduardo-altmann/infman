#ifndef MAP_H
#define MAP_H

#include "game_structs.h"

void initBlock(BLOCK *block, Vector2 position, BlockType type);
void drawBlock(BLOCK block);
bool checkBlockCollision(BLOCK block, PLAYER *player);
void handleBlockCollision(PLAYER *player, BLOCK block);
void drawBlocks(BLOCK blocks[], int n_blocks);
void parseMap(char fileName[], BLOCK blocks[], int *n_blocks, PLAYER *player, ENEMY enemies[], int *n_enemies);
BACKGROUND initBackground(char filename[], float levelWidth, float screenHeight);
void drawBackground(BACKGROUND bg, Camera2D camera);
void unloadBackground(BACKGROUND *bg);
void gui(PLAYER *player);

#endif
