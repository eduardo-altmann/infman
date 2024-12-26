#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

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
}PLAYER;

void initPlayer(PLAYER *player);

void drawPlayer (PLAYER player);

bool playerCollided(PLAYER *player, Rectangle floor);

void updatePlayerX(PLAYER *player);

void updatePlayerY(PLAYER *player, Rectangle floor);

void updatePlayerAnimation(PLAYER *player);

void updatePlayerState(PLAYER *player);

#endif
