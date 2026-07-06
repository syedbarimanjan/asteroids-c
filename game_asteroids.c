#include "game_asteroids.h"
#include "game_score.h"
#include "constants.h"
#include "debug.h"

#include "raymath.h"

static Asteroid _asteroids[MAX_ASTEROIDS] = {0} ;
static AsteroidSize _sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM, ASTEROID_LARGE};
static float _lastAsteroidCreationTime = -1.0f;
static Texture2D _textureAsteroid;

void AddAsteroid(Vector2 position, AsteroidSize size,float speedMod, bool spawn){
  bool created = false;

  Vector2 velocity = spawn ? Vector2Subtract(SCREEN_CENTER,position) : Vector2Rotate((Vector2){0,1}, (float)GetRandomValue(0,359));
  velocity = Vector2Scale(Vector2Normalize(velocity), speedMod * GetRandomValue(ASTEROID_SPEED_MIN,ASTEROID_SPEED_MAX));

  SetLastCone(position,velocity);

  velocity = Vector2Rotate(velocity,(float)GetRandomValue(-ASTEROID_RANDOM_ANGLE,ASTEROID_RANDOM_ANGLE));

  for (int i = 0; i < MAX_ASTEROIDS; i++)
  {
    if (_asteroids[i].active){
      continue;
    }
    _asteroids[i] = CreateAsteroid(position,velocity,size);
    created = true;
    break;
  }

  if(!created) {
    TraceLog(LOG_ERROR, "Failed to create an asteroid because there were no inactive spots in the array!");
  }

}

void DestroyAsteroid(int index, float angle) {
  const float largeSpeedMod = 0.5f;
  const float mediumSpeedMod = 0.33f;
  Asteroid* asteroid = _asteroids + index;
  asteroid->active = false;

  // _newAsteroidsBaseAngle = angle;
  int points = ASTEROID_BASE_SCORE * (int)asteroid->size;
  switch (asteroid->size)
  {
  case ASTEROID_LARGE:
    AddAsteroid(asteroid->position, ASTEROID_MEDIUM,largeSpeedMod, false);
    AddAsteroid(asteroid->position, ASTEROID_MEDIUM,largeSpeedMod, false);
    break;
  case ASTEROID_MEDIUM:
    AddAsteroid(asteroid->position, ASTEROID_SMALL,mediumSpeedMod, false);
    AddAsteroid(asteroid->position, ASTEROID_SMALL,mediumSpeedMod, false);
    break;
  }

  AddScore(points);
}

Vector2 GetNextAsteroidPosition(void){
  int padding = 128;
  Vector2 result = {-padding, -padding};

  if(GetRandomValue(0, 1)){
    if(GetRandomValue(0, 1)){
      result.y = SCREEN_HEIGHT + padding;
    }
    result.x = GetRandomValue(-padding, SCREEN_WIDTH + padding);
  } else {
    if(GetRandomValue(0, 1)){
      result.x = SCREEN_WIDTH + padding;
    }
    result.y = GetRandomValue(-padding, SCREEN_HEIGHT + padding);
  }
  return result;
}

int UpdateAsteroids(void){
  int activeAsteroids = 0;

  float frametime = GetFrameTime();
  float time = GetTime();

  for (int i = 0; i < MAX_ASTEROIDS; i++){
    if (AsteroidUpdate(_asteroids + i, frametime,time)) {
      activeAsteroids++;
    }
  }

  if (time > _lastAsteroidCreationTime + ASTEROID_DELAY)
  {
    AsteroidSize nextSize = _sizes[GetRandomValue(0,2)];
    AddAsteroid(GetNextAsteroidPosition(), nextSize,1.0f,true);
    _lastAsteroidCreationTime = time;
  }

  return activeAsteroids;
}

void DrawAsteroids(void) {
  _textureAsteroid = LoadTexture("assets/asteroid.png");
  for (int i = 0; i < MAX_ASTEROIDS; i++){
    AsteroidDraw(_asteroids[i],_textureAsteroid);
  }
}

Asteroid* AsteroidsArray(void) {
  return _asteroids;
}

void ResetAsteroids(void) {
  for (int i = 0; i < MAX_ASTEROIDS; i++)
  {
    _asteroids[i] = (Asteroid){0} ;
    _lastAsteroidCreationTime = -1.0f;
  }

}
