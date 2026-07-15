#pragma once
#include "tile.h"
#include "common.h"

void FindPath(Tile tiles[12][20], TilePos start, TilePos goal, TilePos* path, int* pathLength);
