#pragma once

#include "room.h"
#include "hero.h"
#include "constants.h"
#include "common.h"

typedef struct Transitioner{
	bool flag;
	int offset;
	int speed;
	Direction direction;
}Transitioner;

typedef struct Map{
	Room rooms[MAP_HEIGHT][MAP_WIDTH];
	Room* currentRoom;
	Room* nextRoom;
	Transitioner transitioner;
}Map;

void LoadMap(Map* map, Assets* assets);
void LoadTransitioner(Transitioner* transitioner);
void CheckTransition(Map* map, Vector2 heroPos);
void UpdateTransition(Map* map, Hero* hero, float dt);
