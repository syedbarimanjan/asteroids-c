#include "asteroids.h"
#include "raymath.h"
#include <raylib.h>

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size) {
  return (Asteroid) {
    .active = true,
    .position = position,
    .velocity = velocity,
    .size = size,
    .rotation = GetRandomValue(0,360),
    .rotationSpeed = GetRandomValue(ASTEROID_ROTATION_SPEED_MIN, ASTEROID_ROTATION_SPEED_MAX),
    .creationTime = GetTime(),
  };
}

bool AsteroidUpdate(Asteroid* asteroid, float frametime, float time) {
  if(!asteroid->active){
      return false;
  }

  if(time > asteroid->creationTime + ASTEROID_LIFE) {
    asteroid->active = false;
    return true;
  }

  asteroid->position = Vector2Add(asteroid->position,Vector2Scale(asteroid->velocity, frametime));
  asteroid->rotation += asteroid->rotationSpeed * frametime;
}

void AsteroidDraw(Asteroid asteroid, Texture2D texture){
  if(!asteroid.active){
    return;
  }

  const Rectangle source = {0,0,32,32};
  Rectangle dest = {asteroid.position.x,asteroid.position.y,AsteroidRadius(asteroid) * 1.5,AsteroidRadius(asteroid) * 1.5};
  Vector2 origin = {dest.width / 2, dest.height /2};

  DrawTexturePro(texture, source, dest, origin, asteroid.rotation, WHITE);
}

float AsteroidRadius(Asteroid asteroid) {
  return 16.0f * (int)asteroid.size;
}
