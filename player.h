#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"

#define PLAYER_RADIUS 24
#define PLAYER_PROJECTILE_OFFSET PLAYER_RADIUS
#define PLAYER_FIRE_DELAY 0.33F

typedef enum PlayerState {
  PLAYER_DEFAULT = 0,
  PLAYER_STUNNED,
  PLAYER_IFRAME,
  PLAYER_DEAD,
} PlayerState;

typedef struct Player
{
  Vector2 position;
  Vector2 velocity;
  PlayerState state;
  float timeStateEntered;
  float rotation;
  float lastFireTime;
} Player;

void PlayerMove(Player* player);
void PlayerDraw(Player player, Texture2D texture);
void PlayerSetState(Player* player,PlayerState state);
Vector2 PlayerFacingDirection(Player player);

#endif