#pragma once

typedef enum{
	NO_DIRECTION,
	NORTH,
	EAST,
	SOUTH,
	WEST
}Direction;

typedef enum{
	IDLE,
	WALK,
	ATTACK,
	CHASE
}Action;

typedef struct TilePos{
	int x;
	int y;
}TilePos;
