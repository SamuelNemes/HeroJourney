#include "room.h"
#include "constants.h"

void LoadRoom(Room* room, Assets* assets, char* path, int row, int col){
	for(int i=0; i < MAX_ENEMIES; i++){
		room->enemies[i].active = false;
	}

	room->row = row;
	room->col = col;
	FileSection section = NONE;
	FILE* f = fopen(path, "r");
	if(!f) return;

	char line[256];
	int tileRow = 0;
	int enemyCount = 0;
	while(fgets(line, sizeof(line), f)){
		if(strcmp(line, "TILEMAP\n") == 0){
			section = TILEMAP;
			continue;
		}else if(strcmp(line, "END TILEMAP\n") == 0){
			section = NONE;
			continue;
		}else if(strcmp(line, "ENEMIES\n") == 0){
			section = ENEMIES;
			continue;
		}else if(strcmp(line, "END ENEMIES\n") == 0){
			section = NONE;
			continue;
		}
		
		switch(section){
			case TILEMAP:
			{
				char* token = strtok(line, " ");
				for(int col=0; col < ROOM_COLS; col++){
					LoadTile(&room->tiles[tileRow][col], atoi(token), tileRow, col);
					token = strtok(NULL, " ");
				}
				tileRow++;
				break;
			}
			case ENEMIES:
			{
				char* token = strtok(line, " ");
				int type = atoi(token);
				token = strtok(NULL, " ");
				int x = atoi(token) * TILE_SIZE;
				token = strtok(NULL, " ");
				int y = atoi(token) * TILE_SIZE;
				LoadEnemy(&room->enemies[enemyCount], assets, type, x, y);

				enemyCount++;
				break;
			}
		}
	}

	fclose(f);
}
