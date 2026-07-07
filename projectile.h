#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "raylib.h"

// extern int PROJECTILE_SPEED;
// extern float PROJECTILE_THICKNESS;
// extern float PROJECTILE_LENGTH;

typedef struct Projectile {
  bool active;

  Vector2 position;
  float rotation;
  float creationTime;

  int speed;
  float thickness;
  float length;
} Projectile;

Projectile CreateProjectile(Vector2 position, float rotation);
bool ProjectileUpdate(Projectile* projectile, float frametime, float time);
void ProjectileDraw(Projectile projectile);

#endif
