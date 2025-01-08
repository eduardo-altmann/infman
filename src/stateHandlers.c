#include "stateHandlers.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "menu.h"
#include "completeLevel.h"
#include <stdio.h>


void loopUpdates(PLAYER *player, BLOCK blocks[], int *n_blocks, ENEMY enemies[], int *n_enemies, GameState *currentState, Camera2D *camera, JOGADOR top5[], int lowerIndex, char *text, int *letterCount, char *fileName){
    if (*currentState == DEATH_STATE) {
        updateDeathScreen(currentState, player, enemies, n_enemies, blocks, n_blocks);
        return;
    } else if(*currentState == SCORE_STATE){
        updateAndDrawScoreScreen(currentState, top5);
        return;
    } else if(*currentState == LEVEL_COMPLETE_STATE){
        updateAndDrawCompleteLevelScreen(currentState, player, enemies, n_enemies, blocks, n_blocks, top5, lowerIndex, text, letterCount, fileName);
        return;
    }
        
    updatePlayerX(player, *n_blocks, blocks);
    updatePlayerY(player, *n_blocks, blocks);
    updatePlayerState(player);
    updatePlayerAnimation(player);
    handleShooting(player);
    updatePlayerProjectiles(player);

    updateEnemiesAndProjectiles(enemies, *n_enemies, player->projectiles, N_BULLETS, player);

    handlePlayerDamage(player, blocks, *n_blocks, enemies, *n_enemies);
    handleDeath(player, currentState);
    handleEnd(player, currentState, blocks, n_blocks);

    camera->target.x = player->position.x - ((1200/3)/2) + 12;
}

void gameDrawUpdates(PLAYER *player, Camera2D *camera, BACKGROUND *bg, ENEMY enemies[], int *n_enemies, BLOCK blocks[], int *n_blocks){
    BeginMode2D(*camera);
        drawBackground(*bg, *camera);
        drawBlocks(blocks, *n_blocks);
        drawPlayer(*player);
        drawPlayerProjectiles(*player);
        drawEnemies(enemies, *n_enemies);
                        
    EndMode2D();
    gui(player);
}

void resetGameState(PLAYER *player, ENEMY enemies[], int *n_enemies, BLOCK blocks[], int *n_blocks) {
    *n_enemies = 0;
    
    *n_blocks = 0;
    
    player->lives = 3;
    player->points = 0;
    player->beingHit = false;
    player->damageCooldown = 0;
    player->isShooting = false;
    player->shootCooldown = 0;
    player->position = (Vector2){0, 0};
    player->speed = (Vector2){0, 0};
    player->initialized = false;
    
    for (int i = 0; i < N_BULLETS; i++) {
        player->projectiles[i].isActive = false;
    }
}