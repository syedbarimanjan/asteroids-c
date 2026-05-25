#include "projectile.h"

#include <math.h>

#define PROJECTILE_SPEED 500
#define PROJECTILE_LIFE 2.0f
#define PROJECTILE_THICKNESS 10.0f
#define PROJECTILE_LENGTH 30.0f
#define PROJECTILE_COLOR CLITERAL(Color){245,201,207,255}

Projectile CreateProjectile(Vector2 position, float rotation) {
  return (Projectile) {
    .position = position,
    .rotation = rotation,
    .active = true,
    .creationTime = GetTime(),
  };
}

bool ProjectileUpdate(Projectile* projectile, float frametime, float time) {
  if(!projectile->active) {
    return false;
  }
  if(time > projectile->creationTime  + PROJECTILE_LIFE){
    projectile->active = false;
    return false;
  }
  
  //https://www.reddit.com/r/learnmath/comments/1fe2kuu/can_someone_explain_the_polar_coordinate_system/
  double radians = DEG2RAD * (projectile->rotation - 90.0f);
  projectile->position.x += PROJECTILE_SPEED * cos(radians) * frametime;
  projectile->position.y += PROJECTILE_SPEED * sin(radians) * frametime;

  return true;
}

void ProjectileDraw(Projectile projectile) {
  if (!projectile.active) {
    return;
  }
  Rectangle rect = {projectile.position.x, projectile.position.y, PROJECTILE_THICKNESS, PROJECTILE_LENGTH};
  // float originY = positionIsMiddle ? length / 2 : length;
  Vector2 origin = {(rect.width / 2), (rect.height / 2)};
  DrawRectanglePro(rect, origin, projectile.rotation, PROJECTILE_COLOR);
}