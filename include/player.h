#ifndef PLAYER_H
#define PLAYER_H

#include "game_structs.h"

void initPlayer(PLAYER *player, Vector2 position);
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
void handlePlayerDamage(PLAYER *player, BLOCK blocks[], int n_blocks, ENEMY enemies[], int n_enemies);
bool isPlayerHitByEnemies(PLAYER *player, ENEMY enemies[], int n_enemies);
bool playerHitSpike(PLAYER *player, BLOCK block);
bool isPlayerSpiked(PLAYER *player, BLOCK blocks[], int n_blocks);
bool isPlayerAboveBlock(PLAYER *player, BLOCK block);
void handleDeath(PLAYER *player, GameState *currentState);
bool playerHitEndBlock(PLAYER *player, BLOCK block);
bool isPlayerAtEnd(PLAYER *player, BLOCK blocks[], int n_blocks);
void handleEnd(PLAYER *player, GameState *currentState, BLOCK blocks[], int *n_blocks);
#endif
