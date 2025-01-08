#include "map.h"
#include "enemy.h"
#include "player.h"
#include <stdio.h>
#include <math.h>

void initBlock(BLOCK *block, Vector2 position, BlockType type){
    block->position = position;
    block->size = (Vector2){16, 16};
    block->type = type;
    if (type == NORMAL_BLOCK) block->texture = LoadTexture("assets/sprites/tile1.png");
    else if(type == SPIKE_BLOCK) block->texture = LoadTexture("assets/sprites/spike.png");
    else if(type == END_BLOCK) block->texture = LoadTexture("assets/sprites/end.png");
}

void drawBlock(BLOCK block){
    Rectangle source = {0, 0, 16, 16};

    Rectangle dest = {
        block.position.x, 
        block.position.y, 
        source.width,
        source.height
        };

     DrawTexturePro(block.texture, source, dest, (Vector2){0,0}, 0.0f, WHITE);
}

bool checkBlockCollision(BLOCK block, PLAYER *player) {
    Rectangle playerHitbox = {player->position.x, player->position.y, player->size.x, player->size.y};
    Rectangle blockHitbox = {block.position.x, block.position.y, 16, 16};
    return CheckCollisionRecs(playerHitbox, blockHitbox);
}

void handleBlockCollision(PLAYER *player, BLOCK block) {
    if (!checkBlockCollision(block, player)) return;
    
    float prevLeft = player->position.x - player->speed.x;
    float prevTop = player->position.y - player->speed.y;
    
    float blockLeft = block.position.x;
    float blockRight = block.position.x + block.size.x;
    float blockTop = block.position.y;
    float blockBottom = block.position.y + block.size.y;
    
    
    if (prevTop + player->size.y <= blockTop) {
        player->position.y = blockTop - player->size.y;
        player->speed.y = 0;
        player->jumpAllowed = true;
        return;
    }
    else if (prevTop >= blockBottom) {
        player->position.y = blockBottom;
        player->speed.y = 0;
        return;
    }
    
    if (prevLeft + player->size.x <= blockLeft) {
        player->position.x = blockLeft - player->size.x;
        player->speed.x = 0;
    }
    else if (prevLeft >= blockRight) {
        player->position.x = blockRight;
        player->speed.x = 0;
    }
}

void drawBlocks(BLOCK blocks[], int n_blocks){
    for (int i = 0; i < n_blocks; i++){
        drawBlock(blocks[i]);
    }
}

void parseMap(char fileName[], BLOCK blocks[], int *n_blocks, PLAYER *player, ENEMY enemies[], int *n_enemies) {
    FILE *arq = fopen(fileName, "r");
    if (!arq) {
        printf("erro!!!");
        return;
    }

    int startY = GetScreenHeight() - (12 * 16);
    int row = 0;

    char line[201]; 
    while (fgets(line, sizeof(line), arq)) {
        int col = 0;
        while (line[col] != '\0' && line[col] != '\n') {
            Vector2 position = (Vector2){col * 16, startY + (row * 16)};
            
            switch (line[col]) {
                case ' ':
                    break;

                case 'B':
                    initBlock(&blocks[*n_blocks], position, NORMAL_BLOCK);
                    (*n_blocks)++;
                    break;

                case 'O':
                    initBlock(&blocks[*n_blocks], position, SPIKE_BLOCK);
                    (*n_blocks)++;
                    break;

                case 'M':
                    initEnemy(&enemies[*n_enemies], position);
                    (*n_enemies)++;
                    break;

                case 'P':
                    position = (Vector2){position.x, position.y-8};
                    initPlayer(player, position);
                    break;
                case 'E':
                    initBlock(&blocks[*n_blocks], position, END_BLOCK);
                    (*n_blocks)++;
                    break;
                
                default:
                    printf("Caractere desonhecido!\n");
                    break;
            }
            col++;
        }
        row++;
    }

    fclose(arq);
}

BACKGROUND initBackground(char filename[], float levelWidth, float screenHeight) {
    BACKGROUND bg = { 0 };
    bg.texture = LoadTexture(filename);
    
    bg.numTiles = (int)ceil(levelWidth / bg.texture.width) + 1;
    bg.position = (Vector2){ 0, 0};
    return bg;
}

void drawBackground(BACKGROUND bg, Camera2D camera) {
    float startX = (camera.target.x - 224) - (camera.offset.x / camera.zoom);
    
    int firstTile = (int)(startX / bg.texture.width);
    
    for (int i = 0; i < bg.numTiles; i++) {
        float xPos = (firstTile + i) * bg.texture.width;
        
        Rectangle source = {
            0, 
            0, 
            bg.texture.width, 
            bg.texture.height
        };
        
        Rectangle dest = {
            xPos,
            GetScreenHeight()-200,
            bg.texture.width,
            bg.texture.height
        };
        
        DrawTexturePro(
            bg.texture,
            source,
            dest,
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );
    }
}

void unloadBackground(BACKGROUND *bg) {
    UnloadTexture(bg->texture);
}

void gui(PLAYER *player) {
    char lifeText[16];
    snprintf(lifeText, sizeof(lifeText), "Life: %d", player->lives);

    char scoreText[16];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", player->points);
    DrawRectangle(5, 5, 200, 70, DARKBLUE);
    DrawText(lifeText, 10, 10, 30, YELLOW);
    DrawText(scoreText, 10, 45, 30, YELLOW);
}
