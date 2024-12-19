#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "projectile.h"

#define N_BULLETS 10

typedef struct {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    bool jumpAllowed;
    bool facingRight;
    Texture2D spriteSheet;
    Rectangle *currentAnimation;
    int frameCount;              
    int currentFrameIndex;       
    float frameTime;             
    float frameSpeed;   
    PROJECTILE projectiles[N_BULLETS];        
}PLAYER;

void initPlayer(PLAYER *player);

void drawPlayer (PLAYER player);

bool playerCollided(PLAYER *player, Rectangle floor);

void updatePlayerX(PLAYER *player);

void updatePlayerY(PLAYER *player, Rectangle floor);

void updatePlayerAnimation(PLAYER *player);

void updatePlayerState(PLAYER *player);

bool isShooting(PLAYER player);

void handleShooting(PLAYER player);

void updatePlayerProjectiles(PLAYER player);

void drawPlayerProjectiles(PLAYER player);

#endif
