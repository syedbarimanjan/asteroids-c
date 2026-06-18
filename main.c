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
#include "game_player.h"
#include "game_ui.h"


void UpdateDrawFrame(void);

int main() {
  srand(time(0));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids in C");
  InitPlayer();


  while(!WindowShouldClose()){
    UpdateDrawFrame();
  }

  CloseWindow();
}

void UpdateDrawFrame(void){
  int activeAsteroids = UpdateAsteroids();
  int activeProjectiles = UpdateProjectiles();
  UpdatePlayer();

  BeginDrawing();
    ClearBackground(NEARBLACK);

    DrawAsteroids();
    DrawProjectiles();
    DrawPlayer();
    DrawScore();
    DrawHealth();
    ShowDebugVisualizations(activeAsteroids);
    ShowDebugMenu();

    // DrawLineAngle(_player.position, _player.rotation, 100, 20, false);
  EndDrawing();
}