#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "map.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define FPS 60

int main(void){
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "INFMAN");
    SetTargetFPS(FPS);

    BACKGROUND background;
    background = initBackground("assets/sprites/background.png", 3200, 200);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, (-3 * 600) +600};
    camera.rotation = 0.0f;
    camera.zoom = 3;

    PLAYER megaman;
    ENEMY enemies[5];
    BLOCK blocks[160];

    int n_enemies = 0;
    int n_blocks = 0;

    parseMap("./maps/map.txt", blocks, &n_blocks, &megaman, enemies, &n_enemies);

    while(!WindowShouldClose()){
        updatePlayerX(&megaman, n_blocks, blocks);
        updatePlayerY(&megaman, n_blocks, blocks);
        updatePlayerState(&megaman);
        updatePlayerAnimation(&megaman);
        handleShooting(&megaman);
        updatePlayerProjectiles(&megaman);

        updateEnemiesAndProjectiles(enemies, n_enemies, megaman.projectiles, N_BULLETS);

        handlePlayerDamage(&megaman, blocks, n_blocks, enemies, n_enemies);

        camera.target.x = megaman.position.x - ((1200/3)/2) + 12;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                drawBackground(background, camera);
                drawBlocks(blocks, n_blocks);
                drawPlayer(megaman);
                drawPlayerProjectiles(megaman);
                drawEnemies(enemies, n_enemies);
            EndMode2D();
            
        EndDrawing();
    }
    unloadBackground(&background);

    return 0;
}
