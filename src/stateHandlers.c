#include "stateHandlers.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "menu.h"


void loopUpdates(PLAYER *player, BLOCK blocks[], int *n_blocks, ENEMY enemies[], int *n_enemies, GameState *currentState, Camera2D *camera){
    updatePlayerX(player, *n_blocks, blocks);
    updatePlayerY(player, *n_blocks, blocks);
    updatePlayerState(player);
    updatePlayerAnimation(player);
    handleShooting(player);
    updatePlayerProjectiles(player);

    updateEnemiesAndProjectiles(enemies, *n_enemies, player->projectiles, N_BULLETS, player);

    handlePlayerDamage(player, blocks, *n_blocks, enemies, *n_enemies);
    handleDeath(player, currentState);

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
