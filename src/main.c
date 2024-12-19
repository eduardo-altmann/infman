#include "raylib.h"
#include "player.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define FPS 60

int main(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "INFMAN");
    SetTargetFPS(FPS);

    PLAYER megaman;
    Rectangle floor = {0, SCREEN_HEIGHT-16, SCREEN_WIDTH, 16};

    initPlayer(&megaman);

    while(!WindowShouldClose()){
        updatePlayerX(&megaman);
        updatePlayerY(&megaman, floor);
        updatePlayerState(&megaman);
        updatePlayerAnimation(&megaman);
        handleShooting(megaman);
        updatePlayerProjectiles(megaman);


        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleRec(floor, BLUE);
            drawPlayer(megaman);
            drawPlayerProjectiles(megaman);
            
        EndDrawing();
    }

    return 0;
}
