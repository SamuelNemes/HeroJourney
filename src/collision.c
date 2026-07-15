#include "raylib.h"
#include "constants.h"
#include "common.h"
#include "collision.h"
#include <stdio.h>

bool CheckHeroTileCollision(Hero* hero, Tile tiles[ROOM_ROWS][ROOM_COLS], float dt){

	Vector2 nextPos = UpdatePosition(hero->pos, hero->velocity, dt);
	Rectangle nextHitBox = {0,0,0,0};
	UpdateHeroHitbox(&nextHitBox, nextPos);

	TilePos currentTile = {hero->hitBox.x / TILE_SIZE, hero->hitBox.y / TILE_SIZE};

	if(hero->velocity.x > 0){
		if(currentTile.x + 1 < ROOM_COLS){
			if(CheckCollisionRecs(nextHitBox, tiles[currentTile.y][currentTile.x+1].pos)
					&& tiles[currentTile.y][currentTile.x+1].isSolid){
				hero->pos.x = tiles[currentTile.y][currentTile.x+1].pos.x - HERO_HITBOX_XOFFSET - HERO_HITBOX_WIDTH;
				UpdateHeroHitbox(&hero->hitBox, hero->pos);
				return true;
			}
			if(currentTile.y + 1 < ROOM_ROWS){
				if(CheckCollisionRecs(nextHitBox, tiles[currentTile.y+1][currentTile.x+1].pos)
						&& tiles[currentTile.y+1][currentTile.x+1].isSolid){
					hero->pos.x = tiles[currentTile.y+1][currentTile.x+1].pos.x - HERO_HITBOX_XOFFSET - HERO_HITBOX_WIDTH;
					UpdateHeroHitbox(&hero->hitBox, hero->pos);
					return true;
				}
			}
		}
	}else if(hero->velocity.x < 0){
		if(currentTile.x - 1 >= 0){
			if(CheckCollisionRecs(nextHitBox, tiles[currentTile.y][currentTile.x-1].pos) 
					&& tiles[currentTile.y][currentTile.x-1].isSolid){
				hero->pos.x = tiles[currentTile.y][currentTile.x-1].pos.x + TILE_SIZE - HERO_HITBOX_XOFFSET;
				UpdateHeroHitbox(&hero->hitBox, hero->pos);
				return true;
			}
			if(currentTile.y + 1 < ROOM_ROWS){
				if(CheckCollisionRecs(nextHitBox, tiles[currentTile.y+1][currentTile.x-1].pos) 
						&& tiles[currentTile.y+1][currentTile.x-1].isSolid){
					hero->pos.x = tiles[currentTile.y+1][currentTile.x-1].pos.x + TILE_SIZE - HERO_HITBOX_XOFFSET;
					UpdateHeroHitbox(&hero->hitBox, hero->pos);
					return true;
				}
			}
		}
	}else if(hero->velocity.y > 0){
		if(currentTile.y + 1 < ROOM_ROWS){
			if(CheckCollisionRecs(nextHitBox, tiles[currentTile.y+1][currentTile.x].pos) 
					&& tiles[currentTile.y+1][currentTile.x].isSolid){
				hero->pos.y = tiles[currentTile.y+1][currentTile.x].pos.y - HERO_HITBOX_HEIGHT - HERO_HITBOX_YOFFSET;
				UpdateHeroHitbox(&hero->hitBox, hero->pos);
				return true;
			}
			if(currentTile.x + 1 < ROOM_COLS){
				if(CheckCollisionRecs(nextHitBox, tiles[currentTile.y+1][currentTile.x+1].pos)
						&& tiles[currentTile.y+1][currentTile.x+1].isSolid){
					hero->pos.y = tiles[currentTile.y+1][currentTile.x+1].pos.y - HERO_HITBOX_HEIGHT - HERO_HITBOX_YOFFSET;
					UpdateHeroHitbox(&hero->hitBox, hero->pos);
					return true;
				}
			}
		}
	}else if(hero->velocity.y < 0){
		if(currentTile.y - 1 >= 0){
			if(CheckCollisionRecs(nextHitBox, tiles[currentTile.y-1][currentTile.x].pos)
					&& tiles[currentTile.y-1][currentTile.x].isSolid){
				hero->pos.y = tiles[currentTile.y-1][currentTile.x].pos.y + TILE_SIZE - HERO_HITBOX_YOFFSET;
				UpdateHeroHitbox(&hero->hitBox, hero->pos);
				return true;
			}
			if(currentTile.x + 1 < ROOM_COLS){
				if(CheckCollisionRecs(nextHitBox, tiles[currentTile.y-1][currentTile.x+1].pos)
						&& tiles[currentTile.y-1][currentTile.x+1].isSolid){
					hero->pos.y = tiles[currentTile.y-1][currentTile.x+1].pos.y + TILE_SIZE - HERO_HITBOX_YOFFSET;
					UpdateHeroHitbox(&hero->hitBox, hero->pos);
					return true;
				}
			}
		}
	}
	return false;
}

bool CheckHeroEnemyCollision(Hero* hero, Enemy enemy[MAX_ENEMIES], Enemy** attacker){
	int count = 0;

	while(enemy[count].active){
		if(CheckCollisionRecs(hero->hitBox, enemy[count].hitBox)){
			*attacker = &enemy[count];
			return true;
		}
		count++;
	}
	return false;
}

bool CheckSwordEnemyCollision(Vector2 swordPos, Vector2 swordPivot, Enemy* enemy){
	Vector2 topRight = {enemy->hitBox.x + enemy->hitBox.width, enemy->hitBox.y};
	Vector2 bottomRight = {enemy->hitBox.x + enemy->hitBox.width, enemy->hitBox.y + enemy->hitBox.height};
	Vector2 topLeft = {enemy->hitBox.x, enemy->hitBox.y};
	Vector2 bottomLeft = {enemy->hitBox.x, enemy->hitBox.y + enemy->hitBox.height};
	if(CheckCollisionLines(swordPivot, swordPos, topLeft, topRight, NULL)){return true;}
	if(CheckCollisionLines(swordPivot, swordPos, topRight, bottomRight, NULL)){return true;}
	if(CheckCollisionLines(swordPivot, swordPos, bottomRight, bottomLeft, NULL)){return true;}
	if(CheckCollisionLines(swordPivot, swordPos, bottomLeft, topLeft, NULL)){return true;}

	return false;
}
