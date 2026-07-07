#ifndef POWERUP_H_
#define POWERUP_H_

#include <raylib.h>

typedef enum PowerupType{
  POWERUP_LIFE,
  POWERUP_BULLETS_SPEED,
  POWERUP_BULLETS_SIZE,
} PowerupType;


typedef struct PowerUp {
  bool active;
  PowerupType type;
  Vector2 position;
  float creationTime;
  float duration;
} PowerUp;

PowerUp CreatePowerup(Vector2 position,PowerupType powerupType);
void DrawPowerup(PowerUp powerup);

#endif
