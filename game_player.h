#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "player.h"

#define PLAYER_HEALTH_MAX 5

void InitPlayer(void);
void DrawPlayer(void);
void UpdatePlayer(void);
int PlayerHealth(void);
void ResetPlayer(void);

#endif