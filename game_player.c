#include "game_player.h"
#include "game_asteroids.h"
#include "game_powerup.h"
#include "game_projectiles.h"
#include "constants.h"
#include "player.h"
#include "powerup.h"
#include "raymath.h"
#include "game.h"

static Player _player;
static Texture2D _texturePlayer;
static int _health = PLAYER_HEALTH_MAX;


void InitPlayer(void){
  ResetPlayer();
  _texturePlayer = LoadTexture("assets/ship.png");
}

void ResetPlayer(void) {
  _player = (Player) {
    .position = SCREEN_CENTER,
    .velocity = (Vector2) {0},
    .rotation = 0,
    .lastFireTime = -1.0f,
    .state = PLAYER_DEFAULT
  };
  _health = PLAYER_HEALTH_MAX;
}

void DrawPlayer(void){
  PlayerDraw(_player,_texturePlayer);
}

static void OnDeath(void){
  PlayerSetState(&_player,PLAYER_DEAD);
}

static void OnCollision(Asteroid* asteroid){
  const float playerNudgeMagnitude = 200.0f;
  const float asteroidSpeedReduction = 0.4f;

  _health--;
  if(_health <= 0){
    OnDeath();
    return;
  }

  PlayerSetState(&_player,PLAYER_STUNNED);

  Vector2 nudgeDirection = Vector2Normalize(Vector2Subtract(_player.position,asteroid->position));
  _player.velocity = Vector2Scale(nudgeDirection,playerNudgeMagnitude);

  asteroid->velocity = Vector2Scale(asteroid->velocity,asteroidSpeedReduction);
}

static void TickState(void){
  const float stunDuration = 0.2f;
  const float iframeDuration = 0.8f;
  const float playerDeathDelay = 1.5f;

  switch (_player.state)
  {
  case PLAYER_DEFAULT:
    break;
  case PLAYER_STUNNED:
    if((GetTime() - _player.timeStateEntered) > stunDuration){
      PlayerSetState(&_player,PLAYER_IFRAME);
    }
    break;
  case PLAYER_IFRAME:
    if((GetTime() - _player.timeStateEntered) > iframeDuration){
      PlayerSetState(&_player,PLAYER_DEFAULT);
    }
    break;
  case PLAYER_DEAD:
    if((GetTime() - _player.timeStateEntered) > playerDeathDelay){
      GameOver();
    }
    break;
  default:
    break;
  }
}

void UpdatePlayer(void){
  TickState();
  PlayerMove(&_player);

  if(_player.state == PLAYER_STUNNED) {
    return;
  }

  PowerUp* powerup = GetPowerups();
  // Projectile* projectiles = GetProjectile();
  float time = GetTime();
  if (IsKeyDown(KEY_SPACE)){
    if(time > _player.lastFireTime + PLAYER_FIRE_DELAY) {
      AddProjectile(Vector2Add(_player.position, Vector2Scale(PlayerFacingDirection(_player),PLAYER_PROJECTILE_OFFSET)), _player.rotation);
      _player.lastFireTime = time;
    }
  }


  for (int i = 0; i < MAX_POWERUPS; i++){
    if(powerup[i].type == POWERUP_LIFE && _health < 5 && DestroyPowerup(&_player, powerup[i])){
      _health += 1;
    }
    // if(powerup[i].type == POWERUP_BULLETS_SPEED && DestroyPowerup(&_player, powerup[i])){
    //   projectiles->speed += 50;
    // }
  }

  if(_player.state == PLAYER_IFRAME) {
    return;
  }

  // using quadtrees will be faster, todo use quadtrees instead.
  Asteroid* asteroids = AsteroidsArray();
  const int count = MAX_ASTEROIDS;

  for(int i = 0; i < count; i++) {
    Asteroid* asteroid = asteroids + i;

    if(!asteroid->active) {
      continue;
    }

    if(!CheckCollisionCircles(_player.position,PLAYER_RADIUS,asteroid->position,AsteroidRadius(*asteroid))){
      continue;
    }

    OnCollision(asteroid);

    break;
  }
}

int PlayerHealth(void){
  return _health;
}

Player* GetPlayer(void){
  return &_player;
}
