#include "game.h"
#include "game_asteroids.h"
#include "game_projectiles.h"
#include "game_powerup.h"
#include "game_score.h"
#include "game_player.h"
#include "game_ui.h"
#include "debug.h"
#include "constants.h"

#include "raygui.h"

static int _activeAsteroids = 0;

extern bool _quitGame;

typedef enum GameState {
  GAME_MAIN_MENU = 0,
  GAME_PLAYING,
  GAME_OVER
} GameState;

static GameState _state;

static void SetState(GameState state){
  switch (state)
  {
  case GAME_MAIN_MENU:
    break;
  case GAME_PLAYING:
    ResetAsteroids();
    ResetPlayer();
    ResetProjectiles();
    ResetScore();
    ResetPowerups();
    break;
  case GAME_OVER:
    break;

  default:
    break;
  }
  _state = state;
}

void InitGame(void){
  InitPlayer();
}

void UpdateGame(void){
  _activeAsteroids = UpdateAsteroids();
  UpdateProjectiles();
  UpdatePlayer();
  UpdatePowerups();
}

void DrawGame(void){
  const int buttonWidth = 200;
  const int buttonHeight = 80;
  const Rectangle topButton = {SCREEN_CENTER.x - buttonWidth / 2, SCREEN_CENTER.y - buttonHeight / 2 - 5, buttonWidth,buttonHeight};
  const Rectangle bottomButton = {SCREEN_CENTER.x - buttonWidth / 2, SCREEN_CENTER.y + buttonHeight / 2 + 5, buttonWidth,buttonHeight};

  switch (_state)
  {
  case GAME_MAIN_MENU:{
    const int fontSizeGameInstructions = 24;
    const char* gameInstructions = "Use Arrows to move and space to shoot\n Red powerup gives 1 health\n Blue increases bullets size\n Green increases bullets speed.";
    float measureGameInstructions =MeasureText(gameInstructions,fontSizeGameInstructions);
    DrawText(gameInstructions,SCREEN_CENTER.x-measureGameInstructions/2,fontSizeGameInstructions * 1.5f,fontSizeGameInstructions,WHITE);
    if (GuiButton(topButton, "Asteroids!")){
      SetState(GAME_PLAYING);
      return;
    }

    if (GuiButton(bottomButton, "Quit")){
      _quitGame = true;
      return;
    }
    break;
  }
  case GAME_PLAYING:
    DrawAsteroids();
    DrawProjectiles();
    DrawPowerups();
    DrawPlayer();
    DrawScore();
    DrawHealth();
    ShowDebugVisualizations(_activeAsteroids);
    break;
  case GAME_OVER:
    // DrawAsteroids();

    DrawRectangleRec(SCREEN_AREA,Fade(BLACK,0.5f));

    const int fontSize = 64;
    const char* gameover = "Game Over:(";
    float measure =MeasureText(gameover,fontSize);
    DrawText(gameover,SCREEN_CENTER.x-measure/2,fontSize * 1.5f,fontSize,BLACK);

    DrawScore();

    if (GuiButton(topButton, "Play Again!")){
      SetState(GAME_PLAYING);
      return;
    }

    if (GuiButton(bottomButton, "Quit")){
      _quitGame = true;
      return;
    }

    break;

  default:
    break;
  }
  ShowDebugMenu();
}

void GameOver(void){
  SetState(GAME_OVER);
}
