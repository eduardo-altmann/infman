#ifndef PLAYER_H
#define PLAYER_H

#include "game_structs.h"

void initPlayer(PLAYER *player);
void drawPlayer(PLAYER player);
bool playerCollided(PLAYER *player, Rectangle floor);
void updatePlayerX(PLAYER *player);
void updatePlayerY(PLAYER *player, Rectangle floor);
void updatePlayerAnimation(PLAYER *player);
void updatePlayerState(PLAYER *player);
bool isShooting(PLAYER player);
void handleShooting(PLAYER *player);
void updatePlayerProjectiles(PLAYER *player);
void drawPlayerProjectiles(PLAYER player);

#endif