#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include "asteroids.h"
#include "constants.h"
#include "game_asteroids.h"
#include "debug.h"
#include "player.h"

static Player _player;
static Texture2D _texturePlayer;

void UpdateDrawFrame(void);

int main() {
  srand(time(0));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids in C");

  _player = (Player) {
  .position = SCREEN_CENTER,
  .velocity = (Vector2) {0},
  .rotation = 180,
  };

  _texturePlayer = LoadTexture("assets/ship.png");

  while(!WindowShouldClose()){
    UpdateDrawFrame();
  }

  CloseWindow();
}

void UpdateDrawFrame(void){
  int activeAsteroids = UpdateAsteroids();
  PlayerUpdate(&_player);

  BeginDrawing();
    ClearBackground(NEARBLACK);

    DrawAsteroids();
    PlayerDraw(_player,_texturePlayer);
    ShowDebugVisualizations(activeAsteroids);
    ShowDebugMenu();
  EndDrawing();
}