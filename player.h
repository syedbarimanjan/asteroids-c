#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"

typedef struct Player
{
  Vector2 position;
  Vector2 velocity;
  float rotation;
  float lastFireTime;
} Player;

void PlayerUpdate(Player* player);
void PlayerDraw(Player player, Texture2D texture);

#endif