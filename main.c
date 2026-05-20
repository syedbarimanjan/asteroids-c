#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include "asteroids.h"
#include "constants.h"
#include "game_asteroids.h"
#include "debug.h"

void UpdateDrawFrame(void);

int main() {
  srand(time(0));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids in C");

  while(!WindowShouldClose()){
    UpdateDrawFrame();
  }

  CloseWindow();
}

void UpdateDrawFrame(void){
  int activeAsteroids = UpdateAsteroids();

  BeginDrawing();
    ClearBackground(NEARBLACK);

    DrawAsteroids();
    ShowDebugVisualizations(activeAsteroids);
    ShowDebugMenu();
  EndDrawing();
}