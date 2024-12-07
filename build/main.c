#include "raylib.h"
#include <stdbool.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define FPS 60
#define GRAVITY 20

typedef struct {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    bool jumpAllowed;
}PLAYER;

void initPlayer(PLAYER *player);

void drawPlayer (PLAYER player);

bool playerCollided(PLAYER *player, Rectangle floor);

void updatePlayerX(PLAYER *player);

void updatePlayerY(PLAYER *player, Rectangle floor);

int main(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "INFMAN");
    SetTargetFPS(FPS);

    PLAYER megaman;
    Rectangle floor = {0, SCREEN_HEIGHT-16, SCREEN_WIDTH, 16};

    initPlayer(&megaman);

    while(!WindowShouldClose()){
        updatePlayerX(&megaman);
        updatePlayerY(&megaman, floor);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleRec(floor, BLUE);
            drawPlayer(megaman);
            
        EndDrawing();
    }

    return 0;
}

void initPlayer(PLAYER *player){
    player->position = (Vector2){SCREEN_WIDTH/2.0, SCREEN_HEIGHT-48};
    player->speed = (Vector2){0,0};
    player->size = (Vector2){24, 24};
}

void drawPlayer (PLAYER player){
    DrawRectangleV(player.position, player.size, RED);
}

bool playerCollided(PLAYER *player, Rectangle floor){
    Rectangle playerHitbox = {player->position.x, player->position.y, player->size.x, player->size.y};

    bool collided = CheckCollisionRecs(playerHitbox, floor);

    return collided;
}

void updatePlayerX(PLAYER *player){
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        player->speed.x += 3;
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->speed.x -= 3;
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
