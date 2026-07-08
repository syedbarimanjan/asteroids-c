#include "projectile.h"
#include "constants.h"
#include "game_player.h"
#include "game_powerup.h"
#include "player.h"
#include "powerup.h"

#include <math.h>
#include <raylib.h>

#define PROJECTILE_LIFE 2.0f
#define PROJECTILE_COLOR RED


Projectile CreateProjectile(Vector2 position, float rotation) {
  return (Projectile) {
    .position = position,
    .rotation = rotation,
    .active = true,
    .creationTime = GetTime(),
    .speed = 500,
    .thickness = 10.0f,
    .length = 30.0f,
  };
}

bool ProjectileUpdate(Projectile* projectile, float frametime, float time) {
  if(!projectile->active) {
    return false;
  }

  if(time > projectile->creationTime  + PROJECTILE_LIFE || !CheckCollisionPointRec(projectile->position,SCREEN_AREA)){
    projectile->active = false;
    return false;
  }

  //https://www.reddit.com/r/learnmath/comments/1fe2kuu/can_someone_explain_the_polar_coordinate_system/
  double radians = DEG2RAD * (projectile->rotation - 90.0f);
  projectile->position.x += projectile->speed * cos(radians) * frametime;
  projectile->position.y += projectile->speed * sin(radians) * frametime;

  return true;
}

void ProjectileDraw(Projectile projectile) {
  if (!projectile.active) {
    return;
  }
  Rectangle rect = {projectile.position.x, projectile.position.y, projectile.thickness, projectile.length};

  Vector2 origin = {(rect.width / 2), (rect.height / 2)};
  DrawRectanglePro(rect, origin, projectile.rotation, PROJECTILE_COLOR);
}
