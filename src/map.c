#include "map.h"
#include <stdio.h>

void initBlock(BLOCK *block, Vector2 position, BlockType type){
    block->position = position;
    block->size = (Vector2){16, 16};
    block->type = type;
    if (type == NORMAL_BLOCK) block->texture = LoadTexture("assets/sprites/tile1.png");
    else if(type == SPIKE_BLOCK) block->texture = LoadTexture("assets/sprites/spike.png");
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

bool checkBlockCollision(BLOCK block, PLAYER *player){
    Rectangle playerHitbox = {player->position.x, player->position.y, player->size.x, player->size.y};

    Rectangle blockHitbox = {block.position.x, block.position.y, 16, 16};

    bool collided = CheckCollisionRecs(playerHitbox, blockHitbox);

    if (collided && block.type == SPIKE_BLOCK) player->beingSpiked = true;
    else player->beingSpiked = false;

    return collided;
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
