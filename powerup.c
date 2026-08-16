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
    DrawCircle(powerup.position.x, powerup.position.y, 20, RED);
    DrawCircleGradient(powerup.position.x, powerup.position.y, 20, WHITE, RED);
    // DrawText("+1 HP",powerup.position.x,powerup.position.y,5,BLACK);
  }
  if(powerup.type == POWERUP_BULLETS_SPEED){
    DrawCircle(powerup.position.x, powerup.position.y, 20, GREEN);
    DrawCircleGradient(powerup.position.x, powerup.position.y, 20, WHITE, GREEN);
    // DrawText("2x Bullets Speed",powerup.position.x,powerup.position.y,5,BLACK);
  }
  if(powerup.type == POWERUP_BULLETS_SIZE){
    DrawCircle(powerup.position.x, powerup.position.y, 20, BLUE);
    DrawCircleGradient(powerup.position.x, powerup.position.y, 20, WHITE, BLUE);
    // DrawText("2x Bullets size",powerup.position.x,powerup.position.y,5,BLACK);
  }
}
