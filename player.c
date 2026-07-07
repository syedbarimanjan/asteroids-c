#include "player.h"
#include "debug.h"
#include "raymath.h"
#include "math.h"
#include "constants.h"
#include "game_projectiles.h"

#define PLAYER_ROTATION_SPEED 360
#define PLAYER_MOVEMENT_SPEED 250
#define PLAYER_ACCELERATION_SPEED 750
#define PLAYER_DECELERATION_SPEED 175
#define PLAYER_NUDGE_VELOCITY 100

#define FIELD_MAX_X (SCREEN_WIDTH + PLAYER_RADIUS / 2)
#define FIELD_MIN_X (-PLAYER_RADIUS / 2)
#define FIELD_MAX_Y (SCREEN_HEIGHT + PLAYER_RADIUS / 2)
#define FIELD_MIN_Y (-PLAYER_RADIUS / 2)

static void UpdateAngle(Player* player, float frametime) {
  if(player->state == PLAYER_STUNNED){
    return;
  }
  int xIn = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
  player->rotation += (xIn * PLAYER_ROTATION_SPEED * frametime);
}

static void UpdateVelocity(Player* player, float frametime){
  if(player->state == PLAYER_STUNNED){
    return;
  }
  int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);
  float magSqr = Vector2LengthSqr(player->velocity);
  float mag = sqrt(magSqr);
  Vector2 facingDirection = PlayerFacingDirection(*player);
  if (yIn > 0) {
    player->velocity = Vector2Add(player->velocity,Vector2Scale(facingDirection, PLAYER_ACCELERATION_SPEED * frametime));
    float mag = Vector2Length(player->velocity);
    if (mag > PLAYER_MOVEMENT_SPEED) {
      player->velocity = Vector2Scale(player->velocity, PLAYER_MOVEMENT_SPEED / mag);
    }
  }
  else {
    if (mag > 0) {
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

  return;
}

static void UpdateWrap(Player* player, float frametime) {
  if(player->position.x > FIELD_MAX_X) {
    player->position.x = FIELD_MIN_X;
    if(player->velocity.x < PLAYER_NUDGE_VELOCITY) {
      player->velocity.x = PLAYER_NUDGE_VELOCITY;
    }
  }
  else if (player->position.x < FIELD_MIN_X) {
    player->position.x = FIELD_MAX_X;
    if(player->velocity.x > -PLAYER_NUDGE_VELOCITY) {
      player->velocity.x = -PLAYER_NUDGE_VELOCITY;
    }
  }

  if(player->position.y > FIELD_MAX_Y) {
    player->position.y = -FIELD_MIN_Y;
    if(player->velocity.y < PLAYER_NUDGE_VELOCITY) {
      player->velocity.y = PLAYER_NUDGE_VELOCITY;
    }
  }
  else if (player->position.y < FIELD_MIN_Y) {
    player->position.y = FIELD_MAX_Y;
    if(player->velocity.y > -PLAYER_NUDGE_VELOCITY) {
      player->velocity.y = -PLAYER_NUDGE_VELOCITY;
    }
  }
}

void PlayerMove(Player* player) {
  float frametime = GetFrameTime();
  float time = GetTime();

  if(player->state != PLAYER_STUNNED && player->state != PLAYER_DEAD){
    UpdateAngle(player,frametime);
    UpdateVelocity(player,frametime);
  }

  player->position = Vector2Add(player->position,Vector2Scale(player->velocity, frametime));

  UpdateWrap(player,frametime);

  SetPlayerInfo(player->position,player->velocity,player->rotation);
}

void PlayerDraw(Player player, Texture2D texture) {
  if(player.state == PLAYER_DEAD) {
    return;
  }
  // DrawPoly(player.position, 3,32,player.rotation,RAYWHITE);
  const Rectangle source = {0,0,32,32};
  Rectangle dest = {player.position.x,player.position.y,PLAYER_RADIUS * 2,PLAYER_RADIUS * 2};
  Vector2 origin = {dest.width / 2, dest.height /2};

  Color color = (player.state == PLAYER_STUNNED) ? RED : (player.state == PLAYER_IFRAME) ? PINK : WHITE;

  DrawTexturePro(texture,source,dest,origin, player.rotation,color);
}

void PlayerSetState(Player* player,PlayerState state){
  player->state = state;
  player->timeStateEntered = GetTime();
}

Vector2 PlayerFacingDirection(Player player){
  return Vector2Rotate((Vector2){0,-1},player.rotation *DEG2RAD);
}
//15:56
