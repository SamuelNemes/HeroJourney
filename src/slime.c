#include "slime.h"
#include "enemy.h"
#include "pathfinder.h"
#include "movement.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void LoadSlime(Slime* slime){
	slime->pathLength = 0;
	for(int i=0; i < ROOM_ROWS * ROOM_COLS; i++){
		slime->path[i] = (TilePos){0, 0};
	}
	slime->pathIndex = 0;
	slime->waypointIndex = 0;
	
	char* tok;
	slime->waypointCount = 0;
	while((tok = strtok(NULL, ", ")) != NULL){
		slime->waypoints[slime->waypointCount].x = atoi(tok);
		tok = strtok(NULL, ", ");
		slime->waypoints[slime->waypointCount].y = atoi(tok);
		slime->waypointCount++;
	}
}

void UpdateSlimeHitbox(Rectangle* hitBox, Vector2 pos){
	*hitBox = (Rectangle){(pos.x + SLIME_HITBOX_XOFFSET), (pos.y + SLIME_HITBOX_YOFFSET), SLIME_HITBOX_WIDTH, SLIME_HITBOX_HEIGHT};
}
void UpdateSlime(Enemy* enemy, Tile tiles[ROOM_ROWS][ROOM_COLS], Vector2 heroPos, float dt){

	enemy->velocity = (Vector2){0, 0};
	enemy->direction = SOUTH;
	enemy->action = IDLE;

	TilePos tilePos = {(int)(enemy->pos.x / TILE_SIZE), (int)(enemy->pos.y / TILE_SIZE)};
	//printf("X: %f\tY: %f\n", enemy->pos.x, enemy->pos.y);
	if(enemy->as.slime.pathLength == 0 
			|| enemy->as.slime.pathIndex >= enemy->as.slime.pathLength){

		enemy->as.slime.pathIndex = 0;

		TilePos destination = {enemy->as.slime.waypoints[enemy->as.slime.waypointIndex].x, enemy->as.slime.waypoints[enemy->as.slime.waypointIndex].y};

		FindPath(tiles, tilePos, destination, enemy->as.slime.path, &enemy->as.slime.pathLength);
		//printf("WAY INDEX: %d\n", enemy->as.slime.waypointIndex);
		enemy->as.slime.waypointIndex++;
		//
		if(enemy->as.slime.pathLength == 0){
			return;
		}
		//
		if(enemy->as.slime.waypointIndex >= enemy->as.slime.waypointCount){
			enemy->as.slime.waypointIndex = 0;
		}
	}

	Vector2 destinationVect = (Vector2){enemy->as.slime.path[enemy->as.slime.pathIndex].x * TILE_SIZE, enemy->as.slime.path[enemy->as.slime.pathIndex].y * TILE_SIZE};
	
	if(enemy->pos.y > destinationVect.y){
		enemy->direction = NORTH;
		enemy->action = WALK;
		enemy->velocity.y = -enemy->speed;
	}else if(enemy->pos.x < destinationVect.x){
		enemy->direction = EAST;
		enemy->action = WALK;
		enemy->velocity.x = enemy->speed;
	}else if(enemy->pos.y < destinationVect.y){
		enemy->direction = SOUTH;
		enemy->action = WALK;
		enemy->velocity.y = enemy->speed;
	}else if(enemy->pos.x > destinationVect.x){
		enemy->direction = WEST;
		enemy->action = WALK;
		enemy->velocity.x = -enemy->speed;
	}
	
	enemy->pos = UpdatePosition(enemy->pos, enemy->velocity, dt);
	
	switch(enemy->direction){
		case NORTH:
			if(enemy->pos.y < destinationVect.y){
				enemy->pos.y = destinationVect.y;
				enemy->as.slime.pathIndex++;
			}
			break;
		case EAST:
			if(enemy->pos.x > destinationVect.x){
				enemy->pos.x = destinationVect.x;
				enemy->as.slime.pathIndex++;
			}
			break;
		case SOUTH:
			if(enemy->pos.y > destinationVect.y){
				enemy->pos.y = destinationVect.y;
				enemy->as.slime.pathIndex++;
			}
			break;
		case WEST:
			if(enemy->pos.x < destinationVect.x){
				enemy->pos.x = destinationVect.x;
				enemy->as.slime.pathIndex++;
			}
			break;
	}

	if(enemy->action != IDLE){Animate(&enemy->animator, dt);}
	enemy->animator.frameRect.x = enemy->animator.baseX + enemy->animator.frame * enemy->animator.frameRect.width;

	UpdateSlimeHitbox(&enemy->hitBox, enemy->pos);

}
