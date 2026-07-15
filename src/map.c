#include "map.h"
#include "room.h"
#include "constants.h"
void LoadTransitioner(Transitioner* transitioner){
	transitioner->flag = false;
	transitioner->offset = 0;
	transitioner->speed = 125;
	transitioner->direction = NO_DIRECTION;
}
void LoadMap(Map* map, Assets* assets){
	char path[64];
	for(int i=0; i < MAP_HEIGHT; i++){
		for(int j=0; j < MAP_WIDTH; j++){
			snprintf(path, sizeof(path), "assets/rooms/room_%02d_%02d.txt", i, j);
			LoadRoom(&map->rooms[i][j], assets, path, i, j);
		}
	}
	map->currentRoom = &map->rooms[0][0];
	map->nextRoom = nullptr;
	LoadTransitioner(&map->transitioner);
}

void CheckTransition(Map* map, Vector2 heroPos){
	if((heroPos.x + HERO_WIDTH) > GAME_WIDTH && map->currentRoom->col + 1 < MAP_WIDTH){
		map->transitioner.flag = true;
		int count = 0;
		while(map->currentRoom->enemies[count].active){
			map->currentRoom->enemies[count].pos = map->currentRoom->enemies[count].origin;
			//
			map->currentRoom->enemies[count].as.slime.pathLength = 0;
			map->currentRoom->enemies[count].as.slime.pathIndex = 0;
			//
			count++;
		}
		map->transitioner.direction = EAST;
		map->nextRoom = &map->rooms[map->currentRoom->row][map->currentRoom->col + 1];
	}else if(heroPos.x < 0 && map->currentRoom->col - 1 > -1){
		map->transitioner.flag = true;
		int count = 0;
		while(map->currentRoom->enemies[count].active){
			map->currentRoom->enemies[count].pos = map->currentRoom->enemies[count].origin;
			//
			map->currentRoom->enemies[count].as.slime.pathLength = 0;
			map->currentRoom->enemies[count].as.slime.pathIndex = 0;
			//
			count++;
		}
		map->transitioner.direction = WEST;
		map->nextRoom = &map->rooms[map->currentRoom->row][map->currentRoom->col - 1];
	}else if(heroPos.y < 0 && map->currentRoom->row - 1 > -1){
		map->transitioner.flag = true;
		int count = 0;
		while(map->currentRoom->enemies[count].active){
			map->currentRoom->enemies[count].pos = map->currentRoom->enemies[count].origin;
			//
			map->currentRoom->enemies[count].as.slime.pathLength = 0;
			map->currentRoom->enemies[count].as.slime.pathIndex = 0;
			//
			count++;
		}
		map->transitioner.direction = NORTH;
		map->nextRoom = &map->rooms[map->currentRoom->row - 1][map->currentRoom->col];
	}else if((heroPos.y + HERO_HEIGHT) > GAME_HEIGHT && map->currentRoom->row + 1 < MAP_HEIGHT){
		map->transitioner.flag = true;
		int count = 0;
		while(map->currentRoom->enemies[count].active){
			map->currentRoom->enemies[count].pos = map->currentRoom->enemies[count].origin;
			//
			map->currentRoom->enemies[count].as.slime.pathLength = 0;
			map->currentRoom->enemies[count].as.slime.pathIndex = 0;
			//
			count++;
		}
		map->transitioner.direction = SOUTH;
		map->nextRoom = &map->rooms[map->currentRoom->row + 1][map->currentRoom->col];
	}
}

void UpdateTransition(Map* map, Hero* hero, float dt){
	if(map->transitioner.direction == NORTH || map->transitioner.direction == SOUTH){
		if(map->transitioner.offset == GAME_HEIGHT){
			if(map->transitioner.direction == NORTH){
				hero->pos.y = GAME_HEIGHT - HERO_HEIGHT;
			}else hero->pos.y = 0;

			map->transitioner.flag = false;
			map->transitioner.offset = 0;
			map->transitioner.direction = NO_DIRECTION;
			map->currentRoom = map->nextRoom;
			map->nextRoom = nullptr;
		}
		if(map->transitioner.offset < GAME_HEIGHT){
			map->transitioner.offset += map->transitioner.speed * dt;
		}
		if(map->transitioner.offset > GAME_HEIGHT){
			map->transitioner.offset = GAME_HEIGHT;
		}
	}else if(map->transitioner.direction == EAST || map->transitioner.direction == WEST){
		if(map->transitioner.offset == GAME_WIDTH){
			if(map->transitioner.direction == WEST){
				hero->pos.x = GAME_WIDTH - HERO_WIDTH;
			}else hero->pos.x = 0;

			map->transitioner.flag = false;
			map->transitioner.offset = 0;
			map->transitioner.direction = NO_DIRECTION;
			map->currentRoom = map->nextRoom;
			map->nextRoom = nullptr;
		}
		if(map->transitioner.offset < GAME_WIDTH){
			map->transitioner.offset += map->transitioner.speed * dt;
		}
		if(map->transitioner.offset > GAME_WIDTH){
			map->transitioner.offset = GAME_WIDTH;
		}
	}
}
