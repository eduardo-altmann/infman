#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "raylib.h"

#define N_BULLETS 10

typedef struct projectile{
    Vector2 position;
    float speed;
    Vector2 size;
    bool isActive;
    bool movingRight;
} PROJECTILE;

typedef struct player{
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
    int lives;
    float damageCooldown;
    float maxDamageCooldown;
    bool beingHit;
    int points;
    bool initialized;
} PLAYER;

typedef struct enemy{
    Vector2 position;
    float speed;
    Vector2 size;
    Texture2D spriteSheet;
    int frameCount;              
    int currentFrameIndex;       
    float frameTime;             
    float frameSpeed; 
    Rectangle *currentAnimation;
    bool facingRight;
    bool isAlive;
    float patrolDistance;
    float initialX;
} ENEMY;

typedef enum {
    NORMAL_BLOCK,
    SPIKE_BLOCK
} BlockType;

typedef struct block {
    Vector2 position;
    Vector2 size;
    Texture2D texture;
    BlockType type;
} BLOCK;

typedef struct AnimationState {
    Rectangle* animation;
    int frameCount;
    float frameSpeed;
} AnimationState;

typedef struct background {
    Texture2D texture;
    Vector2 position;
    int numTiles;
} BACKGROUND;

typedef enum {
    MENU_STATE,
    GAME_STATE,
    DEATH_STATE,
    SCORE_STATE
} GameState;

#define MAXSCORES 5 

typedef struct{
    char nome[45];
    int pontos;
}JOGADOR;

#endif
