#include "player.h"
#include "debug.h"
#include "raymath.h"
#include "math.h"

#define PLAYER_ROTATION_SPEED 360
#define PLAYER_MOVEMENT_SPEED 250
#define PLAYER_ACCELERATION_SPEED 750
#define PLAYER_DECELERATION_SPEED 175

void PlayerUpdate(Player* player) {
  float frametime = GetFrameTime();
  int xIn = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
  player->rotation -= (xIn * PLAYER_ROTATION_SPEED * frametime);

  int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);
  float mag = Vector2Length(player->velocity);
  if (yIn > 0) {
    Vector2 facingDirection = Vector2Rotate((Vector2) {0,1}, -player->rotation * DEG2RAD);
    player->velocity = Vector2Add(player->velocity,Vector2Scale(facingDirection, PLAYER_ACCELERATION_SPEED * frametime));
    float mag = Vector2Length(player->velocity);
    if (mag > PLAYER_MOVEMENT_SPEED) {
      player->velocity = Vector2Scale(player->velocity, PLAYER_MOVEMENT_SPEED / mag);
    }
  } 
  else {
    if (mag > 0) {
      float magSqr = mag * mag;

      float xSign = (player->velocity.x < 0) ? -1.0f: 1.0f;
      float ySign = (player->velocity.y < 0) ? -1.0f: 1.0f;

      float xAbs = player->velocity.x * xSign;
      float yAbs = player->velocity.y * ySign;
  
      float xWeight = xAbs * xAbs / magSqr;
      float yWeight = yAbs * yAbs / magSqr;

  
      float xDeceleration = xWeight * PLAYER_DECELERATION_SPEED * xSign * frametime;
      float yDeceleration = yWeight * PLAYER_DECELERATION_SPEED * ySign * frametime;
  
      player->velocity.x = (xAbs > xDeceleration) ? player->velocity.x - xDeceleration : 0;
      player->velocity.y = (yAbs > yDeceleration) ? player->velocity.y - yDeceleration : 0;
    }
  }
  
  player->position = Vector2Add(player->position,Vector2Scale(player->velocity, frametime));


  

  SetPlayerInfo(player->position,player->velocity,player->rotation);
}

void PlayerDraw(Player player, Texture2D texture) {
  // DrawPoly(player.position, 3,32,player.rotation,RAYWHITE);
  const Rectangle source = {0,0,32,32};
  Rectangle dest = {player.position.x,player.position.y,48,48};
  Vector2 origin = {dest.width / 2, dest.height /2};
  DrawTexturePro(texture,source,dest,origin,180 - player.rotation,WHITE);
}

