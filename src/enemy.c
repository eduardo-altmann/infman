#include "raylib.h"
#include "enemy.h"

#define FRAME_0 (Rectangle) {0, 0, 16, 24}
#define FRAME_1 (Rectangle) {17, 0, 16, 24}

Rectangle animation[2] = {FRAME_0, FRAME_1};

void initEnemy(ENEMY *enemy, Vector2 position){
    enemy->position.x = position.x;
    enemy->position.y = position.y - 10;
    enemy->speed = 1.0;
    enemy->size = (Vector2){16, 24};
    enemy->spriteSheet = LoadTexture("assets/sprites/enemies.png");
    enemy->facingRight = false;
    enemy->currentAnimation = animation; 
    enemy->frameCount = 2;                   
    enemy->currentFrameIndex = 0;
    enemy->frameTime = 0.0f;
    enemy->frameSpeed = 0.1f;
    enemy->isAlive = true;
    enemy->patrolDistance = 96;
    enemy->initialX = position.x;
}

void updateEnemy(ENEMY *enemy){
    if (enemy->facingRight){
        if(enemy->position.x < (enemy->initialX + enemy->patrolDistance)) enemy->position.x += enemy->speed;
        else enemy->facingRight = false;
    } else {
        if(enemy->position.x > (enemy->initialX - enemy->patrolDistance)) enemy->position.x -= enemy->speed;
        else enemy->facingRight = true;
    }
}

void drawEnemy (ENEMY enemy){
    if(enemy.isAlive){
        Rectangle source = enemy.currentAnimation[enemy.currentFrameIndex];

        source.width *= (enemy.facingRight ? -1.0f : 1.0f);

        Rectangle dest = {enemy.position.x, 
            enemy.position.y, 
            source.width,
            source.height
            };

        DrawTexturePro(enemy.spriteSheet, source, dest, (Vector2){0,0}, 0.0f, WHITE);
    }
    
}

void updateEnemyAnimation(ENEMY *enemy) {
    enemy->frameTime += GetFrameTime();

    if (enemy->frameTime >= enemy->frameSpeed) {
        enemy->currentFrameIndex++;
        if (enemy->currentFrameIndex >= enemy->frameCount) {
            enemy->currentFrameIndex = 0; 
        }
        enemy->frameTime = 0.0f; 
    }
}

bool wasEnemyHit(ENEMY *enemy, PROJECTILE bullet){
    Rectangle enemyHitbox = {enemy->position.x, enemy->position.y, enemy->size.x, enemy->size.y};

    Rectangle bulletHitbox = {bullet.position.x, bullet.position.y, bullet.size.x, bullet.size.y};

    return CheckCollisionRecs(enemyHitbox, bulletHitbox);
}

void updateEnemiesAndProjectiles(ENEMY enemies[], int n_enemies, PROJECTILE bullets[], int n_bullets){
    for(int i = 0; i < n_enemies; i++) {
        if(enemies[i].isAlive) {

            updateEnemy(&enemies[i]);
            updateEnemyAnimation(&enemies[i]);
            
            for(int j = 0; j < n_bullets; j++) {
                if(bullets[j].isActive) {
                    if(wasEnemyHit(&enemies[i], bullets[j])) {
                        enemies[i].isAlive = false;
                        bullets[j].isActive = false;
                        break;
                    }
                }
            }
        }
    }
}

void drawEnemies(ENEMY enemies[], int n_enemies){
    for (int i = 0; i < n_enemies; i++){
        drawEnemy(enemies[i]);
    }
}