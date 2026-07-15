#include "goblin.h"
#include "enemy.h"
#include "pathfinder.h"
#include "movement.h"
#include <stdio.h>

void LoadGoblin(Goblin* goblin){
	goblin->pathLength = 0;
	for(int i=0; i < ROOM_ROWS * ROOM_COLS; i++){
		goblin->path[i] = (TilePos){0, 0};
	}
	goblin->pathIndex = 0;
}

void UpdateGoblin(Enemy* enemy, Tile tiles[ROOM_ROWS][ROOM_COLS], Vector2 heroPos, float dt){
}
