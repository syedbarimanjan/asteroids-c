#ifndef GAME_ASTEROIDS_H_
#define GAME_ASTEROIDS_H_

#include "asteroids.h"

void AddAsteroid(Vector2 position, AsteroidSize size);
Vector2 GetNextAsteroidPosition(void);
int UpdateAsteroids(void);
void DrawAsteroids(void);

#endif