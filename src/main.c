#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "menu.h"
#include "stateHandlers.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define FPS 60

int main(void){
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "INFMAN");
    SetTargetFPS(FPS);

    GameState currentState;
    currentState = MENU_STATE;

    BACKGROUND background;
    background = initBackground("assets/sprites/background.png", 3200, 200);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, (-3 * 600) +600};
    camera.rotation = 0.0f;
    camera.zoom = 3;

    PLAYER megaman;
    megaman.initialized = false;
    ENEMY enemies[5];
    BLOCK blocks[160];

    int n_enemies = 0;
    int n_blocks = 0;

    while(!WindowShouldClose()){
        loopUpdates(&megaman, blocks, &n_blocks, enemies, &n_enemies, &currentState, &camera);

        
        BeginDrawing();
            ClearBackground(RAYWHITE);

            switch (currentState) {
                case MENU_STATE:
                    updateAndDrawMenu(&currentState, "./maps/map.txt", blocks, &n_blocks, &megaman, enemies, &n_enemies);
                    break;
                case GAME_STATE:
                    gameDrawUpdates(&megaman, &camera, &background, enemies, &n_enemies, blocks, &n_blocks);
                    break;
                case DEATH_STATE:
                    drawDeathScreen();
                    break;
            }
            
        EndDrawing();
    }
    unloadBackground(&background);

    return 0;
}
