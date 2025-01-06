#ifndef PLAYER_H
#define PLAYER_H

#include "game_structs.h"

void initPlayer(PLAYER *player);
void drawPlayer(PLAYER player);
void updatePlayerX(PLAYER *player, int blockCount, BLOCK blocks[]);
void updatePlayerY(PLAYER *player, int blockCount, BLOCK blocks[]);
void updatePlayerAnimation(PLAYER *player);
void updatePlayerState(PLAYER *player);
bool isShooting(PLAYER player);
void handleShooting(PLAYER *player);
void updatePlayerProjectiles(PLAYER *player);
void drawPlayerProjectiles(PLAYER player);
bool wasPlayerHit(PLAYER *player, ENEMY *enemy);
void causeDamage(PLAYER *player, ENEMY *enemy);


#endif
