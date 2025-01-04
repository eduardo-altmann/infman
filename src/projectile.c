#include "projectile.h"
#include "player.h"
#include "raylib.h"

void initProjectile(const PLAYER *player, PROJECTILE *bullet){
    bullet->position.x = player->position.x;
    bullet->position.y = player->position.y + 10;
    bullet->speed = 15.0;
    bullet->size = (Vector2){6, 3};
    bullet->isActive = true;
    bullet->movingRight = player->facingRight;
}

void updateProjectile(PLAYER *player, PROJECTILE *bullet){
    if (bullet->position.x > GetScreenWidth() || bullet->position.x < 0){
        bullet->isActive = false;
    } else {
        if (bullet->movingRight) bullet->position.x += bullet->speed;
        else bullet->position.x -= bullet->speed;
    }
}

void drawProjectile(PROJECTILE bullet){
    DrawRectangleV(bullet.position, bullet.size, RED);
}
