#ifndef MAP_H
#define MAP_H

#include "game_structs.h"

void initBlock(BLOCK *block, Vector2 position, BlockType type);
void drawBlock(BLOCK block);
bool checkBlockCollision(BLOCK block, PLAYER *player);
void handleBlockCollision(PLAYER *player, BLOCK block);
void drawBlocks(BLOCK blocks[], int n_blocks);

#endif
