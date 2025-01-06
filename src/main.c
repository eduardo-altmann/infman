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

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, (-3.75 * 600) +600};
    camera.rotation = 0.0f;
    camera.zoom = 3.75f;

    PLAYER megaman;
    //Rectangle floor = {0, SCREEN_HEIGHT-16, SCREEN_WIDTH, 16};

    ENEMY enemies[1];

    BLOCK normalBlocks[51];
    BLOCK obstacle;

    initPlayer(&megaman);
    initEnemy(&enemies[0], (Vector2){600, SCREEN_HEIGHT-48});
    for (int i = 0; i < 50; i++){
        initBlock(&normalBlocks[i], (Vector2){i*16, SCREEN_HEIGHT-16}, NORMAL_BLOCK);
    }
    initBlock(&obstacle, (Vector2){160, SCREEN_HEIGHT-32}, SPIKE_BLOCK);
    normalBlocks[50] = obstacle;
    while(!WindowShouldClose()){
        updatePlayerX(&megaman, 51, normalBlocks);
        updatePlayerY(&megaman, 51, normalBlocks);
        updatePlayerState(&megaman);
        updatePlayerAnimation(&megaman);
        handleShooting(&megaman);
        updatePlayerProjectiles(&megaman);

        updateEnemy(&enemies[0]);
        updateEnemyAnimation(&enemies[0]);
        updateEnemiesAndProjectiles(enemies, 1, megaman.projectiles, N_BULLETS);

        causeDamageByEnemies(&megaman, enemies, 1);
        playerSpiked(&megaman);

        camera.target.x = megaman.position.x - ((1200/3.75)/2) + 12;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                drawBlocks(normalBlocks, 51);
                drawPlayer(megaman);
                drawPlayerProjectiles(megaman);
                drawEnemy(enemies[0]);
            EndMode2D();
            
        EndDrawing();
    }

    return 0;
}
