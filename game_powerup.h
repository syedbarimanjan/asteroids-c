#ifndef GAME_POWERUP_H_
#define GAME_POWERUP_H_

#include "player.h"
#include "powerup.h"

#define MAX_POWERUPS 2

void AddPowerup(Vector2 position);
void UpdatePowerups(void);
void DrawPowerups(void);
PowerUp* GetPowerups(void);
bool DestroyPowerup(Player* player,PowerUp powerup);
void ResetPowerups(void);

#endif
