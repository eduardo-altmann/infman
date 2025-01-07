#ifndef ENEMY_H
#define ENEMY_H

#include "game_structs.h"

void initEnemy(ENEMY *enemy, Vector2 position);
void updateEnemy(ENEMY *enemy);
void drawEnemy(ENEMY enemy);
void updateEnemyAnimation(ENEMY *enemy);
bool wasEnemyHit(ENEMY *enemy, PROJECTILE bullet);
void updateEnemiesAndProjectiles(ENEMY enemies[], int n_enemies, PROJECTILE bullets[], int n_bullets);
void drawEnemies(ENEMY enemies[], int n_enemies);

#endif
