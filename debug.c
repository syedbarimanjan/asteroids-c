#include "debug.h"
#include "constants.h"

#include "raymath.h"
#include "raygui.h"


static bool _showDebugMenu = false;
static bool _showAsteroidCount = false;
static bool _showAngleCone = false;

static Vector2 line0[2];
static Vector2 line1[2];

void ShowDebugMenu(void) {
  if(IsKeyPressed(KEY_GRAVE)){
    _showDebugMenu = !_showDebugMenu;
  }

  
    if (_showDebugMenu) {
      Rectangle r = {10,SCREEN_HEIGHT - 40, 20, 20};
      // if (GuiButton(r, "Toggle Asteroid Count"))
      // {
      //   _showAsteroidCount = !_showAsteroidCount;
      // }
  
      // r.x += 180 + 10;
      // if (GuiButton(r, "Show Angle Cone"))
      // {
      //   _showAngleCone = !_showAngleCone;
      // }
       GuiCheckBox(r, "Show asteroid count", &_showAsteroidCount);
      r.y -= 30;
       GuiCheckBox(r,"Show angle cone", &_showAngleCone);
    }
}

void ShowDebugVisualizations(int asteroidCount) {
  if (_showAngleCone) {
      DrawLineV(line0[0],line0[1],RED);
      DrawLineV(line1[0],line1[1],BLUE);
  }
  if (_showAsteroidCount){
    DrawRectangle(10,10,100,52, Fade(BLACK, 0.6f));
    DrawText(TextFormat("ASTEROIDS: %d", asteroidCount), 20, 20, 32, WHITE);
  }
}

void SetLastCone(Vector2 position, Vector2 velocity) {
  line0[0] = position;
  line1[0] = position;

  line0[1] = Vector2Add(position,Vector2Rotate(Vector2Scale(velocity,10), -ASTEROID_RANDOM_ANGLE));
  line1[1] = Vector2Add(position,Vector2Rotate(Vector2Scale(velocity,10), ASTEROID_RANDOM_ANGLE));
}