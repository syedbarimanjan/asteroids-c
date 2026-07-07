#include "powerup.h"
#include <raylib.h>

#define POWERUP_LIFE_DURATION 2.0f

PowerUp CreatePowerup(Vector2 position,PowerupType powerupType){
  return (PowerUp) {
    .position = position,
    .active = true,
    .creationTime = GetTime(),
    .type = powerupType,
    .duration = POWERUP_LIFE_DURATION
  };
}

void DrawPowerup(PowerUp powerup){
  if(!powerup.active){
    return;
  }

  if(powerup.type == POWERUP_LIFE){
    DrawCircle(powerup.position.x, powerup.position.y, 100, RED);
  }
  if(powerup.type == POWERUP_BULLETS_SPEED){
    DrawCircle(powerup.position.x, powerup.position.y, 100, GREEN);
  }
  if(powerup.type == POWERUP_BULLETS_SIZE){
    DrawCircle(powerup.position.x, powerup.position.y, 100, BLUE);
  }
}
