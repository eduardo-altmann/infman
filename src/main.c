#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "menu.h"
#include "stateHandlers.h"
#include "top5.h"
#include "completeLevel.h"

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

    char text[45 + 1] = "\0";
    int letterCount = 0;

    PLAYER megaman;
    megaman.initialized = false;
    ENEMY enemies[5];
    BLOCK blocks[200];

    JOGADOR top5[5];
    char *fileName =  "./save/top5.bin";
    le_arquivo(fileName, top5);
    int lowerIndex = retornaMenorIndice(top5);

    char *mapFile =  "./maps/map.txt";

    int n_enemies = 0;
    int n_blocks = 0;

    while(!WindowShouldClose()){
        loopUpdates(&megaman, blocks, &n_blocks, enemies, &n_enemies, &currentState, &camera, top5, lowerIndex, text, &letterCount, fileName);

        
        BeginDrawing();
            ClearBackground(RAYWHITE);

            switch (currentState) {
                case MENU_STATE:
                    updateAndDrawMenu(&currentState, mapFile, blocks, &n_blocks, &megaman, enemies, &n_enemies);
                    break;
                case GAME_STATE:
                    gameDrawUpdates(&megaman, &camera, &background, enemies, &n_enemies, blocks, &n_blocks);
                    break;
                case DEATH_STATE:
                    drawDeathScreen();
                    break;
                case SCORE_STATE:
                    updateAndDrawScoreScreen(&currentState, top5);
                    break;
                case LEVEL_COMPLETE_STATE:
                    updateAndDrawCompleteLevelScreen(&currentState, &megaman, enemies, &n_enemies, blocks, &n_blocks, top5, lowerIndex, text, &letterCount, fileName);
                    break;
            }
            
        EndDrawing();
    }
    unloadBackground(&background);

    return 0;
}
