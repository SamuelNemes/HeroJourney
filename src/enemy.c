#include "enemy.h"
#include "constants.h"
#include "collision.h"

void LoadEnemy(Enemy* enemy, Assets* assets, int type, int x, int y){
	enemy->active = true;
	enemy->type = type;
	enemy->origin = (Vector2){x, y};

	switch(type){
		case GOBLIN:
			enemy->update = &UpdateGoblin;
			enemy->enemySheet = &assets->goblinSheet;
			LoadGoblin(&enemy->as.goblin);

			enemy->pos = (Vector2){x, y};
			enemy->velocity = (Vector2){0, 0};
			enemy->direction = SOUTH;
			enemy->action = IDLE;
			enemy->speed = 60;
			
			LoadAnimator(&enemy->animator, 0, 0, GOBLIN_WIDTH, GOBLIN_HEIGHT, 0, GOBLIN_WALK_FRAME_COUNT, GOBLIN_WALK_ANIM_RATE);

			enemy->hitBox = (Rectangle){(enemy->pos.x + GOBLIN_HITBOX_XOFFSET), (enemy->pos.y + GOBLIN_HITBOX_YOFFSET), GOBLIN_HITBOX_WIDTH, GOBLIN_HITBOX_HEIGHT};

			break;
		case SLIME:
			enemy->health = 2;
			enemy->update = &UpdateSlime;
			enemy->enemySheet = &assets->slimeSheet;
			LoadSlime(&enemy->as.slime);

			enemy->pos = (Vector2){x, y};
			enemy->velocity = (Vector2){0, 0};
			enemy->direction = SOUTH;
			enemy->action = IDLE;
			enemy->speed = 50;

			LoadAnimator(&enemy->animator, 0, 0, SLIME_WIDTH, SLIME_HEIGHT, 0, SLIME_WALK_FRAME_COUNT, SLIME_WALK_ANIM_RATE);

			enemy->hitBox = (Rectangle){(enemy->pos.x + SLIME_HITBOX_XOFFSET), (enemy->pos.y + SLIME_HITBOX_YOFFSET), SLIME_HITBOX_WIDTH, SLIME_HITBOX_HEIGHT};
			
			break;

	}
}

void UpdateEnemy(Enemy enemies[MAX_ENEMIES], Tile tiles[ROOM_ROWS][ROOM_COLS], Vector2 heroPos, Vector2 swordPos, Vector2 swordPivot, float dt){
	int count = 0;
	while(count < MAX_ENEMIES){
		if(!enemies[count].active){
			count++;
			continue;
		}
		if(CheckSwordEnemyCollision(swordPos, swordPivot, &enemies[count])){
			enemies[count].health--;
		}
		if(enemies[count].health <= 0){
			enemies[count].active = false;
		}
		enemies[count].update(&enemies[count], tiles, heroPos, dt);
		count++;
	}
}
