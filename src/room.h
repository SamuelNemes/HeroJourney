#pragma once
#include "tile.h"
#include "enemy.h"
#include "constants.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum FileSection{
	NONE,
	TILEMAP,
	ENEMIES
}FileSection;

typedef struct Room{
	int row;
	int col;
	Tile tiles[ROOM_ROWS][ROOM_COLS];
	Enemy enemies[MAX_ENEMIES];

}Room;

void LoadRoom(Room* room, Assets* assets, char* path, int row, int col);
