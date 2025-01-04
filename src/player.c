#include "projectile.h"
#include "player.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define GRAVITY 40


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

Rectangle idleAnimation[2] = {FRAME_IDLE_0, FRAME_IDLE_1};
Rectangle runAnimation[3] = {FRAME_RUN_0, FRAME_RUN_1, FRAME_RUN_2};
Rectangle idleShootAnimation[1] = {FRAME_SHOOT_IDLE};
Rectangle runShootAnimation[3] = {FRAME_SHOOT_RUN_0, FRAME_SHOOT_RUN_1, FRAME_SHOOT_RUN_2};

void initPlayer(PLAYER *player) {
    player->position = (Vector2){SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - 48};
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

bool playerCollided(PLAYER *player, Rectangle floor){
    Rectangle playerHitbox = {player->position.x, player->position.y, player->size.x, player->size.y};

    bool collided = CheckCollisionRecs(playerHitbox, floor);

    return collided;
}

void updatePlayerX(PLAYER *player){
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        player->speed.x += 1.5;
        player->facingRight = true;
        
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->speed.x -= 1.5;
        player->facingRight = false;
        
    }

    player->speed.x /= 1.2;

    player->position.x += player->speed.x;
}

void updatePlayerY(PLAYER *player, Rectangle floor){
    player->speed.y += GRAVITY * GetFrameTime();

    if (playerCollided(player, floor)){
        player->position.y = floor.y - player->size.y;
        player->speed.y = 0;
        player->jumpAllowed = true;
    }

    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))&& player->jumpAllowed){
        player->speed.y = -10;
        player->jumpAllowed = false;
    } 

    player->position.y += player->speed.y;
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
    // se o cooldown ainda não terminou, diminui ele
    if (player->shootCooldown > 0){
        player->shootCooldown -= GetFrameTime();
    }
    //se o cooldown terminou e o player ta atirando, atualiza
    if (isShooting(*player) && player->shootCooldown <= 0){
        player->isShooting = true;
        player->shootCooldown = player->maxShootCooldown;
    }
    // se cooldown acabou não ta atirando
    if (player->shootCooldown <= 0){
        player->isShooting = false;
    }
    if(player->isShooting){
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            player->currentAnimation = runShootAnimation;
            player->frameCount = 3;
            player->frameSpeed = 0.15f;
            player->facingRight = true;
        } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            player->currentAnimation = runShootAnimation;
            player->frameCount = 3;
            player->frameSpeed = 0.15f;
            player->facingRight = false;
        } else {
            player->currentAnimation = idleShootAnimation;
            player->frameCount = 1;
            player->frameSpeed = 0.4f;
        }
    } else {
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            player->currentAnimation = runAnimation;
            player->frameCount = 3;
            player->frameSpeed = 0.15f;
            player->facingRight = true;
        } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            player->currentAnimation = runAnimation;
            player->frameCount = 3;
            player->frameSpeed = 0.15f;
            player->facingRight = false;
        } else {
            player->currentAnimation = idleAnimation;
            player->frameCount = 2;
            player->frameSpeed = 0.4f;
        }
    }
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