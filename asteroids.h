#ifndef ASTEROIDS_H_
#define ASTEROIDS_H_

#include "raylib.h"

#define ASTEROID_ROTATION_SPEED_MIN 5
#define ASTEROID_ROTATION_SPEED_MAX 240

#define ASTEROID_SPEED_MIN 100
#define ASTEROID_SPEED_MAX 300
#define ASTEROID_LIFE 10.0f

typedef enum AsteroidSize {
  ASTEROID_SMALL = 1,
  ASTEROID_MEDIUM = 2,
  ASTEROID_LARGE = 4,
} AsteroidSize;

typedef struct Asteroids {
  bool active;

  Vector2 position;
  Vector2 velocity;
  AsteroidSize size;

  float rotation;
  float rotationSpeed;
  float creationTime;
} Asteroid;

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
bool AsteroidUpdate(Asteroid* asteroid, float frametime, float time);
void AsteroidDraw(Asteroid asteroid, Texture2D texture);
// void AddAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
float AsteroidRadius(Asteroid asteroid);

#endif
