#include "game_projectiles.h"

#define PROJECTILE_MAX 12
static Projectile _projectiles[PROJECTILE_MAX];

void AddProjectile(Vector2 position, float rotation){
  bool created = false;

  for (int i = 0; i < PROJECTILE_MAX; i++) {
    if (_projectiles[i].active) {
      continue;
    }

    _projectiles[i] = CreateProjectile(position,rotation);
    created = true;
    break;
  }

  if (!created) {
    TraceLog(LOG_ERROR, "Failed to create a projectile because there were no inactive spots in the array");
  }

  
}

int UpdateProjectiles(void) {
  float frametime = GetFrameTime();
  float time = GetTime();

  int projectileCount = 0;
  for (int i = 0; i < PROJECTILE_MAX; i++) {
    if (ProjectileUpdate(_projectiles + i, frametime,time)) { // can be &_projectiles[i] like this too
      projectileCount++;
    }
  }
  
  return projectileCount;
}

void DrawProjectiles(void) {
  for (int i = 0; i < PROJECTILE_MAX; i++) {
    ProjectileDraw(_projectiles[i]);
  }
}