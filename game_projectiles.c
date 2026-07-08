#include "game_projectiles.h"
#include "game_asteroids.h"
#include "constants.h"
#include "game_player.h"
#include "game_powerup.h"
#include "player.h"
#include "powerup.h"

#define PROJECTILE_MAX 12
static Projectile _projectiles[PROJECTILE_MAX];

Projectile AddProjectile(Vector2 position, float rotation){
  bool created = false;

  for (int i = 0; i < PROJECTILE_MAX; i++) {
    if (_projectiles[i].active) {
      continue;
    }

    Projectile projectile = CreateProjectile(position,rotation);
    Player* player = GetPlayer();
    projectile.speed += player->projectileSpeedBonusPowerup;
    projectile.thickness += player->projectileThicknessBonusPowerup;
    projectile.length += player->projectileLengthBonusPowerup;
    _projectiles[i] = projectile;
    created = true;
    break;
  }

  if (!created) {
    TraceLog(LOG_ERROR, "Failed to create a projectile because there were no inactive spots in the array");
  }
}

static bool CheckCollisionProjectile(Projectile* projectile, Asteroid* asteroid) {
  return !asteroid->active ? false : CheckCollisionPointCircle(projectile->position, asteroid->position,AsteroidRadius(*asteroid));
}

int UpdateProjectiles(void) {
  float frametime = GetFrameTime();
  float time = GetTime();

  Asteroid* asteroids = AsteroidsArray();

  int projectileCount = 0;
  for (int i = 0; i < PROJECTILE_MAX; i++) {
    Projectile* projectile = _projectiles + i;

    if (ProjectileUpdate(projectile, frametime,time)) { // can be &_projectiles[i] like this too
      projectileCount++;

      bool hit = false;
      for(int j = 0; j < MAX_ASTEROIDS; j++) {
        Asteroid* asteroid = asteroids +j;
        if(CheckCollisionProjectile(projectile,asteroid)) {
          hit = true;
          DestroyAsteroid(j,projectile->rotation);
          projectile->active = false;

          break;
        }
      }
    }
  }

  return projectileCount;
}

void DrawProjectiles(void) {
  for (int i = 0; i < PROJECTILE_MAX; i++) {
    ProjectileDraw(_projectiles[i]);
  }
}

void ResetProjectiles(void){
  for (int i = 0; i < PROJECTILE_MAX; i++)
  {
    _projectiles[i] = (Projectile){0};
  }
}

Projectile* GetProjectile(){
  return _projectiles;
}
