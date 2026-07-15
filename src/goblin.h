#pragma once
#include "constants.h"
#include "common.h"
#include "tile.h"

typedef struct Enemy Enemy;	//forward declare enemy struct to avoid circular dependency - research circular dependency further

typedef struct Goblin{
	int pathLength;
	TilePos path[ROOM_ROWS * ROOM_COLS];
	int pathIndex;
}Goblin;

void LoadGoblin(Goblin* goblin);

void UpdateGoblin(Enemy* enemy, Tile tiles[ROOM_ROWS][ROOM_COLS], Vector2 heroPos, float dt);
