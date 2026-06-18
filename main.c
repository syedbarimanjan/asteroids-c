#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include "game_asteroids.h"
#include "game_projectiles.h"
#include "asteroids.h"
#include "constants.h"
#include "debug.h"
#include "player.h"
#include "game_score.h"

static Player _player;
static Texture2D _texturePlayer;

void UpdateDrawFrame(void);

int main() {
  srand(time(0));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids in C");

  _player = (Player) {
  .position = SCREEN_CENTER,
  .velocity = (Vector2) {0},
  .rotation = 0,
  .lastFireTime = -0.1f
  };

  _texturePlayer = LoadTexture("assets/ship.png");

  while(!WindowShouldClose()){
    UpdateDrawFrame();
  }

  CloseWindow();
}

void UpdateDrawFrame(void){
  int activeAsteroids = UpdateAsteroids();
  int activeProjectiles = UpdateProjectiles();
  PlayerUpdate(&_player);

  BeginDrawing();
    ClearBackground(NEARBLACK);

    DrawAsteroids();
    DrawProjectiles();
    PlayerDraw(_player,_texturePlayer);
    DrawScore();
    ShowDebugVisualizations(activeAsteroids);
    ShowDebugMenu();

    // DrawLineAngle(_player.position, _player.rotation, 100, 20, false);
  EndDrawing();
}