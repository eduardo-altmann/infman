#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_structs.h"

void initProjectile(const PLAYER *player, PROJECTILE *bullet);
void updateProjectile(PLAYER *player, PROJECTILE *bullet);
void drawProjectile(PROJECTILE bullet);

#endif