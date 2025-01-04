#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "raylib.h"

#define N_BULLETS 10

typedef struct {
    Vector2 position;
    float speed;
    Vector2 size;
    bool isActive;
    bool movingRight;
} PROJECTILE;

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
    bool isShooting;
    float shootCooldown;
    float maxShootCooldown;
} PLAYER;

#endif