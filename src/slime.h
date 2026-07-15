#pragma once

#include "constants.h"
#include "common.h"
#include "tile.h"

typedef struct Enemy Enemy;

typedef struct Slime{
	int pathLength;
	TilePos path[ROOM_ROWS * ROOM_COLS];
	TilePos waypoints[25];
	int pathIndex;
	int waypointCount;
	int waypointIndex;
}Slime;

void LoadSlime(Slime* slime);

void UpdateSlimeHitbox(Rectangle* hitBox, Vector2 pos);

void UpdateSlime(Enemy* enemy, Tile tiles[ROOM_ROWS][ROOM_COLS], Vector2 heroPos, float dt);
