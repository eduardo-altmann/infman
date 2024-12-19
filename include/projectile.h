#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"
#include "player.h"

typedef struct {
    Vector2 position;
    float speed;
    Vector2 size;
    bool isActive;
}PROJECTILE;

void initProjectile(PLAYER player, PROJECTILE *bullet);
void updateProjectile(PLAYER player, PROJECTILE *bullet);
void drawProjectile(PROJECTILE bullet);

#endif
