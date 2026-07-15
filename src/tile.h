#pragma once

#include "raylib.h"

typedef enum{
	DIRT,
	COBBLE,
	GRASS
}tileType;

typedef struct Tile{
	tileType type;
	Rectangle pos;
	bool isSolid;
}Tile;

void LoadTile(Tile* tile, int type, int row, int col);

Rectangle getTileRect(tileType tile);
