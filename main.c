#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "constants.h"
#include "game.h"


void UpdateDrawFrame(void);

bool _quitGame = false;

int main() {
  srand(time(0));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids in C");
  InitGame();


  while(!WindowShouldClose() && !_quitGame){
    UpdateDrawFrame();
  }

  CloseWindow();
}

void UpdateDrawFrame(void){
  UpdateGame();

  BeginDrawing();
    ClearBackground(NEARBLACK);

    DrawGame();

  EndDrawing();
}