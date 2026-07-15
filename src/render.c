#include "render.h"
#include "map.h"
#include "constants.h"
#include <stdio.h>

void DrawSword(Sword* sword, Texture2D swordSheet){
	Rectangle src = sword->animator.frameRect;
	Rectangle dest = {sword->pivot.x, sword->pivot.y, SWORD_WIDTH, SWORD_HEIGHT};
	Vector2 origin = {0, 0};
	float rotation = sword->currentAngle * (180.0 / PI);
	
	DrawTexturePro(swordSheet, src, dest, origin, rotation, RAYWHITE);
	DrawPixelV(sword->point, RED);
}

void DrawHero(Hero* hero, Texture2D heroSheet, Texture2D swordSheet){
	if(hero->sword.active && hero->direction != SOUTH){
		DrawSword(&hero->sword, swordSheet);
	}
	DrawTextureRec(heroSheet, hero->animator.frameRect, hero->pos, RAYWHITE);
	printf("X: %f\n", hero->animator.frameRect.x);
	printf("Y: %f\n", hero->animator.frameRect.y);
	printf("WIDTH: %f\n", hero->animator.frameRect.width);
	printf("HEIGHT: %f\n", hero->animator.frameRect.height);
	if(hero->sword.active && hero->direction == SOUTH){
		DrawSword(&hero->sword, swordSheet);
	}
}

void DrawEnemy(Enemy* enemy){
	DrawTextureRec(*enemy->enemySheet, enemy->animator.frameRect, enemy->pos, RAYWHITE);
}

void DrawRoom(Room* room, Texture2D tileSheet){
	for(int row = 0; row < ROOM_ROWS; row++){
		for(int col = 0; col < ROOM_COLS; col++){
			Vector2 tilePos = {(col*TILE_SIZE), (row*TILE_SIZE)};	
			DrawTextureRec(tileSheet, getTileRect(room->tiles[row][col].type), tilePos, RAYWHITE);
		}
	}

	for(int i = 0; i < MAX_ENEMIES; i++){
		if(room->enemies[i].active){
			DrawEnemy(&room->enemies[i]);
		}
	}
}

void DrawMap(Map* map, Texture2D tileSheet){
	DrawRoom(map->currentRoom, tileSheet);
}

void DrawHeroTransition(Hero* hero, Texture2D heroSheet, int offset, Direction direction){
	Vector2 tmpPos = {0,0};
	switch(direction){
		case NORTH:
			tmpPos = (Vector2){(hero->pos.x), (hero->pos.y + offset)};
			if(tmpPos.y + HERO_HEIGHT > GAME_HEIGHT){
				tmpPos.y = GAME_HEIGHT - HERO_HEIGHT;
			}
			break;
		case EAST:
			tmpPos = (Vector2){(hero->pos.x - offset), (hero->pos.y)};
			if(tmpPos.x < 0){
				tmpPos.x = 0;
			}
			break;
		case SOUTH:
			tmpPos = (Vector2){(hero->pos.x), (hero->pos.y - offset)};
			if(tmpPos.y < 0){
				tmpPos.y = 0;
			}
			break;
		case WEST:
			tmpPos = (Vector2){(hero->pos.x + offset), (hero->pos.y)};
			if(tmpPos.x  + HERO_WIDTH > GAME_WIDTH){
				tmpPos.x = GAME_WIDTH - HERO_WIDTH;
			}
			break;
	}

	DrawTextureRec(heroSheet, hero->animator.frameRect, tmpPos, RAYWHITE);
}

void DrawMapTransition(Map* map, Texture2D tileSheet){
	DrawRoomTransition(map->currentRoom, map->nextRoom, map->transitioner.direction, map->transitioner.offset, tileSheet);
}

void DrawRoomTransition(Room* currentRoom, Room* nextRoom, Direction direction, int offset, Texture2D tileSheet){
	switch(direction){
		case NORTH:
			for(int row = 0; row < ROOM_ROWS; row++){
				for(int col = 0; col < ROOM_COLS; col++){
					Vector2 tilePos = {(col*TILE_SIZE), (row*TILE_SIZE + offset)};
					Vector2 nextTilePos = {(col * TILE_SIZE), (row*TILE_SIZE - GAME_HEIGHT + offset)};
					DrawTextureRec(tileSheet, getTileRect(currentRoom->tiles[row][col].type), tilePos, RAYWHITE);
					DrawTextureRec(tileSheet, getTileRect(nextRoom->tiles[row][col].type), nextTilePos, RAYWHITE);
				}
			}
			break;
		case EAST:
			for(int row = 0; row < ROOM_ROWS; row++){
				for(int col = 0; col < ROOM_COLS; col++){
					Vector2 tilePos = {(col*TILE_SIZE - offset), (row*TILE_SIZE)};
					Vector2 nextTilePos = {(col*TILE_SIZE + GAME_WIDTH - offset), (row*TILE_SIZE)};
					DrawTextureRec(tileSheet, getTileRect(currentRoom->tiles[row][col].type), tilePos, RAYWHITE);
					DrawTextureRec(tileSheet, getTileRect(nextRoom->tiles[row][col].type), nextTilePos, RAYWHITE);
				}
			}
			break;
		case SOUTH:
			for(int row = 0; row < ROOM_ROWS; row++){
				for(int col = 0; col < ROOM_COLS; col++){
					Vector2 tilePos = {(col*TILE_SIZE), (row*TILE_SIZE - offset)};
					Vector2 nextTilePos = {(col*TILE_SIZE), (row*TILE_SIZE + GAME_HEIGHT - offset)};
					DrawTextureRec(tileSheet, getTileRect(currentRoom->tiles[row][col].type), tilePos, RAYWHITE);
					DrawTextureRec(tileSheet, getTileRect(nextRoom->tiles[row][col].type), nextTilePos, RAYWHITE);
				}
			}
			break;
		case WEST:
			for(int row = 0; row < ROOM_ROWS; row++){
				for(int col = 0; col < ROOM_COLS; col++){
					Vector2 tilePos = {(col*TILE_SIZE + offset), (row*TILE_SIZE)};
					Vector2 nextTilePos = {(col*TILE_SIZE - GAME_WIDTH + offset), (row*TILE_SIZE)};
					DrawTextureRec(tileSheet, getTileRect(currentRoom->tiles[row][col].type), tilePos, RAYWHITE);
					DrawTextureRec(tileSheet, getTileRect(nextRoom->tiles[row][col].type), nextTilePos, RAYWHITE);
				}
			}
			break;
	}
}

void DrawMenu(int health, int maxHealth, Texture2D menu, Texture2D hearts, Texture2D heroCloseup){

	DrawTexture(menu, 0, GAME_HEIGHT, RAYWHITE);

	int totalHeartsDrawn = 0;
	int fullHearts = health / 2;

	for(int i=0; i<fullHearts; i++){
		Rectangle heartRect = {HEART_FULL, 0, HEART_WIDTH, HEART_HEIGHT};
		Vector2 heartPos = {(HEART_XOFFSET + (totalHeartsDrawn * (HEART_WIDTH + HEART_MARGIN))), (GAME_HEIGHT + HEART_YOFFSET)};
		DrawTextureRec(hearts, heartRect, heartPos, RAYWHITE);
		totalHeartsDrawn++;
	}
	
	if(health % 2 == 1){
		Rectangle halfHeartRect = {HEART_HALF, 0, HEART_WIDTH, HEART_HEIGHT};
		Vector2 halfHeartPos = {(HEART_XOFFSET + (totalHeartsDrawn * (HEART_WIDTH + HEART_MARGIN))), (GAME_HEIGHT + HEART_YOFFSET)};
		DrawTextureRec(hearts, halfHeartRect, halfHeartPos, RAYWHITE);
		totalHeartsDrawn++;
	}

	int emptyHearts = (maxHealth - health) / 2;
	int count = 0;
	while(totalHeartsDrawn < (maxHealth / 2)){
		Rectangle emptyHeartRect = {0, 0, HEART_WIDTH, HEART_HEIGHT};
		Vector2 emptyHeartPos = {(HEART_XOFFSET + (totalHeartsDrawn * (HEART_WIDTH + HEART_MARGIN))), (GAME_HEIGHT + HEART_YOFFSET)};
		DrawTextureRec(hearts, emptyHeartRect, emptyHeartPos, RAYWHITE);
		totalHeartsDrawn++;
	}

	if((float)(health) / (float)(maxHealth) > .75){
		Rectangle heroCloseupRect = {0 * HERO_CLOSEUP_WIDTH, 0, HERO_CLOSEUP_WIDTH, HERO_CLOSEUP_HEIGHT};
		Vector2 heroCloseupPos = {HERO_CLOSEUP_XOFFSET, (GAME_HEIGHT + HERO_CLOSEUP_YOFFSET)};
		DrawTextureRec(heroCloseup, heroCloseupRect, heroCloseupPos, RAYWHITE);
	}else if((float)(health) / (float)(maxHealth) > .5){
		Rectangle heroCloseupRect = {1 * HERO_CLOSEUP_WIDTH, 0, HERO_CLOSEUP_WIDTH, HERO_CLOSEUP_HEIGHT};
		Vector2 heroCloseupPos = {HERO_CLOSEUP_XOFFSET, (GAME_HEIGHT + HERO_CLOSEUP_YOFFSET)};
		DrawTextureRec(heroCloseup, heroCloseupRect, heroCloseupPos, RAYWHITE);
	}else if((float)(health) / (float)(maxHealth) > .25){
		Rectangle heroCloseupRect = {2 * HERO_CLOSEUP_WIDTH, 0, HERO_CLOSEUP_WIDTH, HERO_CLOSEUP_HEIGHT};
		Vector2 heroCloseupPos = {HERO_CLOSEUP_XOFFSET, (GAME_HEIGHT + HERO_CLOSEUP_YOFFSET)};
		DrawTextureRec(heroCloseup, heroCloseupRect, heroCloseupPos, RAYWHITE);
	}else{
		Rectangle heroCloseupRect = {3 * HERO_CLOSEUP_WIDTH, 0, HERO_CLOSEUP_WIDTH, HERO_CLOSEUP_HEIGHT};
		Vector2 heroCloseupPos = {HERO_CLOSEUP_XOFFSET, (GAME_HEIGHT + HERO_CLOSEUP_YOFFSET)};
		DrawTextureRec(heroCloseup, heroCloseupRect, heroCloseupPos, RAYWHITE);
	}
}
