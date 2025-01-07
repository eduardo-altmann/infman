#include "projectile.h"
#include "player.h"
#include "map.h"
#include <stdio.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define GRAVITY 50


// sprite sheet coordinates:
#define FRAME_IDLE_0 (Rectangle){0, 0, 24, 24}
#define FRAME_IDLE_1 (Rectangle){24, 0, 24, 24}

#define FRAME_RUN_0 (Rectangle){48, 0, 24, 24}
#define FRAME_RUN_1 (Rectangle){72, 0, 24, 24}
#define FRAME_RUN_2 (Rectangle){96, 0, 24, 24}

#define FRAME_SHOOT_IDLE (Rectangle) {24*5 + 32*2, 0, 32, 24}

#define FRAME_SHOOT_RUN_0 (Rectangle) {24*5 + 32*3, 0, 32, 24}
#define FRAME_SHOOT_RUN_1 (Rectangle) {24*5 + 32*4, 0, 32, 24}
#define FRAME_SHOOT_RUN_2 (Rectangle) {24*5 + 32*5, 0, 32, 24}

#define FRAME_JUMP (Rectangle){120, 0, 32, 32}
#define FRAME_SHOOT_JUMP (Rectangle){310, 0, 32, 32}
#define FRAME_DAMAGE (Rectangle){152, 0, 32, 32}

Rectangle idleAnimation[2] = {FRAME_IDLE_0, FRAME_IDLE_1};
Rectangle runAnimation[3] = {FRAME_RUN_0, FRAME_RUN_1, FRAME_RUN_2};
Rectangle idleShootAnimation[1] = {FRAME_SHOOT_IDLE};
Rectangle runShootAnimation[3] = {FRAME_SHOOT_RUN_0, FRAME_SHOOT_RUN_1, FRAME_SHOOT_RUN_2};
Rectangle damageAnimation[1] = {FRAME_DAMAGE};
Rectangle jumpAnimation[1] = {FRAME_JUMP};
Rectangle jumpShootAnimation[1] = {FRAME_SHOOT_JUMP};

void initPlayer(PLAYER *player, Vector2 position) {
    player->position = position;
    player->speed = (Vector2){0, 0};
    player->size = (Vector2){24, 24};
    player->spriteSheet = LoadTexture("assets/sprites/sprites.png");
    player->facingRight = true;
    player->currentAnimation = idleAnimation; 
    player->frameCount = 2;                   
    player->currentFrameIndex = 0;
    player->frameTime = 0.0f;
    player->frameSpeed = 0.4f;
    for (int i = 0; i < N_BULLETS; i++){
        player->projectiles[i].isActive = false;
    }
    player->isShooting = false;
    player->shootCooldown = 0;
    player->maxShootCooldown = 0.3f;
    player->lives = 3;
    player->damageCooldown = 0;
    player->maxDamageCooldown = 1.0f;
    player->points = 0;
}


void drawPlayer (PLAYER player){
    Rectangle source = player.currentAnimation[player.currentFrameIndex];

    source.width *= (player.facingRight ? -1.0f : 1.0f);

    Rectangle dest = {player.position.x, 
        player.position.y, 
        source.width,
        source.height
        };

    DrawTexturePro(player.spriteSheet, source, dest, (Vector2){0,0}, 0.0f, WHITE);
}

void updatePlayerX(PLAYER *player, int blockCount, BLOCK blocks[]){
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        player->speed.x += 1;
        player->facingRight = true;
        
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->speed.x -= 1;
        player->facingRight = false;
        
    }

    player->speed.x /= 1.2;

    player->position.x += player->speed.x;

    for(int i = 0; i < blockCount; i++) {
        handleBlockCollision(player, blocks[i]);
    }
}

void updatePlayerY(PLAYER *player, int blockCount, BLOCK blocks[]){
    player->speed.y += GRAVITY * GetFrameTime();
    
    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && player->jumpAllowed){
        player->speed.y = -10;
        player->jumpAllowed = false;
    }
    
    player->position.y += player->speed.y;
    

    for(int i = 0; i < blockCount; i++) {
        handleBlockCollision(player, blocks[i]);
    }
}

void updatePlayerAnimation(PLAYER *player) {
    player->frameTime += GetFrameTime();

    if (player->frameTime >= player->frameSpeed) {
        player->currentFrameIndex++;
        if (player->currentFrameIndex >= player->frameCount) {
            player->currentFrameIndex = 0; 
        }
        player->frameTime = 0.0f; 
    }
}

bool isShooting(PLAYER player){
    if (IsKeyPressed(KEY_LEFT_CONTROL)){
        return true;
    }else {
        return false;
    }
}

void updatePlayerState(PLAYER *player) {
    if (player->shootCooldown > 0) {
        player->shootCooldown -= GetFrameTime();
        if (player->shootCooldown <= 0) {
            player->isShooting = false;
        }
    }
    
    if (isShooting(*player) && player->shootCooldown <= 0) {
        player->isShooting = true;
        player->shootCooldown = player->maxShootCooldown;
    }

    AnimationState currentState;
    
    if (player->beingHit) {
        currentState = (AnimationState){damageAnimation, 1, 0.3f};
    }
    else if (player->isShooting && player->speed.y != 0) {
        currentState = (AnimationState){jumpShootAnimation, 1, 0.3f};
    }
    else if (player->isShooting) {
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
            currentState = (AnimationState){runShootAnimation, 3, 0.2f};
        } else {
            currentState = (AnimationState){idleShootAnimation, 1, 0.4f};
        }
    }
    else if (player->speed.y != 0) {
        currentState = (AnimationState){jumpAnimation, 1, 0.3f};
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
        currentState = (AnimationState){runAnimation, 3, 0.2f};
    }
    else {
        currentState = (AnimationState){idleAnimation, 2, 0.4f};
    }

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player->facingRight = true;
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->facingRight = false;
    }

    player->currentAnimation = currentState.animation;
    player->frameCount = currentState.frameCount;
    player->frameSpeed = currentState.frameSpeed;
}

void handleShooting(PLAYER* player){
    if (isShooting(*player)){
        for (int i = 0; i < N_BULLETS; i++){
            if(player->projectiles[i].isActive == false){
                initProjectile(player, &player->projectiles[i]);
                break;
            }
        }
    }
}

void updatePlayerProjectiles(PLAYER* player){
    for (int i = 0; i < N_BULLETS; i++){
        if (player->projectiles[i].isActive){
            updateProjectile(player, &player->projectiles[i]);
        }
    }
}

void drawPlayerProjectiles(PLAYER player){
    for (int i = 0; i < N_BULLETS; i++){
        if(player.projectiles[i].isActive){
            drawProjectile(player.projectiles[i]);
        }
    }
}

bool wasPlayerHit(PLAYER *player, ENEMY *enemy){
    if (enemy->isAlive){
        Rectangle playerHitbox = {player->position.x, player->position.y, player->size.x, player->size.y};

        Rectangle enemyHitbox = {enemy->position.x, enemy->position.y, enemy->size.x, enemy->size.y};

        return CheckCollisionRecs(playerHitbox, enemyHitbox);
    } else return false;
    
}

bool isPlayerHitByEnemies(PLAYER *player, ENEMY enemies[], int n_enemies) {
    for (int i = 0; i < n_enemies; i++) {
        if (enemies[i].isAlive && wasPlayerHit(player, &enemies[i])) {
            return true;
        }
    }
    return false;
}

bool isPlayerAboveBlock(PLAYER *player, BLOCK block) {
    float playerBottom = player->position.y + player->size.y;
    float blockTop = block.position.y;
    
    float playerLeft = player->position.x+8;
    float playerRight = player->position.x + player->size.x-8;
    float blockLeft = block.position.x;
    float blockRight = block.position.x + 16;
    
    bool horizontalOverlap = playerRight > blockLeft && playerLeft < blockRight;
    
    float tolerance = 1.0f;
    bool verticalAlignment = playerBottom >= blockTop && 
                           playerBottom <= blockTop + tolerance &&
                           player->speed.y >= 0;
    
    return horizontalOverlap && verticalAlignment;
}

bool playerHitSpike(PLAYER *player, BLOCK block) {
    return block.type == SPIKE_BLOCK && isPlayerAboveBlock(player, block);
}

bool isPlayerSpiked(PLAYER *player, BLOCK blocks[], int n_blocks) {
    for (int i = 0; i < n_blocks; i++) {
        if (playerHitSpike(player, blocks[i])) {
            return true;
        }
    }
    return false;
}



void handlePlayerDamage(PLAYER *player, BLOCK blocks[], int n_blocks, ENEMY enemies[], int n_enemies) {
    if (player->damageCooldown > 0) {
        player->damageCooldown -= GetFrameTime();
        return; 
    }
    
    player->beingHit = false;
    
    if (isPlayerSpiked(player, blocks, n_blocks)) {
        player->beingHit = true;
        player->damageCooldown = player->maxDamageCooldown;
        player->lives -= 1;
        return;
    }
    
    if (isPlayerHitByEnemies(player, enemies, n_enemies)) {
        player->beingHit = true;
        player->damageCooldown = player->maxDamageCooldown;
        player->lives -= 1;
    }
}

void handleDeath(PLAYER *player, GameState *currentState) {
    if (player->lives <= 0) {
        *currentState = DEATH_STATE;
    }
}
