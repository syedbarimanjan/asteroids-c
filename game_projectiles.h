#ifndef GAME_PROJECTILES_H_
#define GAME_PROJECTILES_H_

#include "projectile.h"

Projectile AddProjectile(Vector2 position, float rotation);
int UpdateProjectiles(void);
void DrawProjectiles(void);
void ResetProjectiles(void);
Projectile* GetProjectile(void);

#endif