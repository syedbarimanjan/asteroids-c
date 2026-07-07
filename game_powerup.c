#include "game_powerup.h"
#include "game_player.h"
#include "player.h"
#include "powerup.h"
#include <raylib.h>
#include <raymath.h>


static PowerUp _powerups[MAX_POWERUPS] = {0} ;

void AddPowerup(Vector2 position){
  bool created = false;


  for (int i = 0; i < MAX_POWERUPS; i++) {
    if (_powerups[i].active) {
      continue;
    }
    PowerupType powerupType = GetRandomValue(0, 2);


    _powerups[i] = CreatePowerup(position,powerupType);
    created = true;
    break;
  }

  if (!created) {
    TraceLog(LOG_ERROR, "Failed to create a PowerUp because there were no inactive spots in the array");
  }
}

bool DestroyPowerup(Player* player,PowerUp powerup) {
  return !powerup.active ? false : CheckCollisionPointCircle(powerup.position, player->position,100);
}

void UpdatePowerups(void){
  Player* player = GetPlayer();
  int playerHealth = PlayerHealth();

  for (int i = 0; i < MAX_POWERUPS; i++){
    if(DestroyPowerup(player, _powerups[i])){
      _powerups[i].active = false;
      // if(_powerups[i].type == POWERUP_LIFE){
      //   // Vector2 direction = Vector2Normalize(player->velocity);
      //   // player->velocity = Vector2Add(Vector2Scale(direction, 20), player->velocity);
      //   playerHealth += 1;
      //   DrawFPS(100, 100);
      // }
    }
    if(player->state == PLAYER_STUNNED){
      int center = GetRandomValue(0, GetScreenWidth());
      AddPowerup((Vector2){center,center});
    }
    if(GetTime() - _powerups[i].creationTime > 50 ){
      _powerups[i].active = false;
    }
  }
}

void DrawPowerups(void) {
  for (int i = 0; i < MAX_POWERUPS; i++){
    DrawPowerup(_powerups[i]);
  }
}

PowerUp* GetPowerups(void) {
  return _powerups;
}

void ResetPowerups(void) {
  for (int i = 0; i < MAX_POWERUPS; i++)
  {
    _powerups[i] = (PowerUp){0};
  }
}
