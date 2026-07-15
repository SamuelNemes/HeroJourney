#include "hero.h"
#include "collision.h"
#include "constants.h"

void LoadHero(Hero* hero){
	hero->pos = (Vector2){4 * TILE_SIZE, 4 * TILE_SIZE};
	hero->velocity = (Vector2){0, 0};
	hero->health = HERO_DEFAULT_HEALTH;
	hero->maxHealth = HERO_DEFAULT_HEALTH;
	hero->direction = SOUTH;	
	hero->action = IDLE;
	hero->speed = 75;
	LoadAnimator(&hero->animator, 0, 0, HERO_WIDTH, HERO_HEIGHT, 0, HERO_WALK_FRAME_COUNT, HERO_WALK_ANIM_RATE);
	hero->hitBox = (Rectangle){(hero->pos.x + HERO_HITBOX_XOFFSET), (hero->pos.y + HERO_HITBOX_YOFFSET), HERO_HITBOX_WIDTH, HERO_HITBOX_HEIGHT};
	LoadSword(&hero->sword);
	hero->hitDelayTimer = 0;

	hero->knockbackTimer = 0;
}

void ReadHeroInput(Hero* hero, SDL_Joystick* joy){

	if(SDL_GetJoystickButton(joy, 1) && !hero->sword.active){
		ActivateSword(&hero->sword, hero->direction, hero->pos);
		hero->action = ATTACK;
		hero->velocity = (Vector2){0, 0};
	}

	if(hero->action == IDLE || hero->action == WALK){	
		hero->velocity = (Vector2){0, 0};
		hero->action = IDLE;
		if(IsKeyDown(KEY_S) || (joy && SDL_GetJoystickAxis(joy, 1) > 16000)){
			hero->velocity.y = hero->speed;
			hero->direction = SOUTH;
			hero->action = WALK;
			hero->animator.frameCount = 2;
		}
		if(IsKeyDown(KEY_W) || (joy && SDL_GetJoystickAxis(joy, 1) < -16000)){
			hero->velocity.y = -hero->speed;
			hero->direction = NORTH;
			hero->action = WALK;
			hero->animator.frameCount = 2;
		}
		if(IsKeyDown(KEY_A) || (joy && SDL_GetJoystickAxis(joy, 0) < -16000)){
			hero->velocity.x = -hero->speed;
			hero->direction = WEST;
			hero->action = WALK;
			hero->animator.frameCount = 2;
		}
		if(IsKeyDown(KEY_D) || (joy && SDL_GetJoystickAxis(joy, 0) > 16000)){
			hero->velocity.x = hero->speed;
			hero->direction = EAST;
			hero->action = WALK;
			hero->animator.frameCount = 2;
		}

		if(hero->velocity.x != 0){ hero->velocity.y = 0; }
	}
}
void UpdateHeroHitbox(Rectangle* hitBox, Vector2 pos){
	*hitBox = (Rectangle){(pos.x + HERO_HITBOX_XOFFSET), (pos.y + HERO_HITBOX_YOFFSET), HERO_HITBOX_WIDTH, HERO_HITBOX_HEIGHT};
}

void ApplyKnockback(Hero* hero, Enemy* attacker){
	hero->velocity = (Vector2){0, 0};
	hero->knockbackTimer = KNOCKBACK_DURATION;
	if(hero->action == WALK){
		switch(hero->direction){
			case NORTH:
				hero->velocity.y = KNOCKBACK_SPEED;
				break;
			case EAST:
				hero->velocity.x = -KNOCKBACK_SPEED;
				break;
			case SOUTH:
				hero->velocity.y = -KNOCKBACK_SPEED;
				break;
			case WEST:
				hero->velocity.x = KNOCKBACK_SPEED;
				break;
		}	
	}else{
		switch(attacker->direction){
			case NORTH:
				hero->velocity.y = -KNOCKBACK_SPEED;
				break;
			case EAST:
				hero->velocity.x = KNOCKBACK_SPEED;
				break;
			case SOUTH:
				hero->velocity.y = KNOCKBACK_SPEED;
				break;
			case WEST:
				hero->velocity.x = -KNOCKBACK_SPEED;
				break;
		}
	}
}

void UpdateHero(Hero* hero, SDL_Joystick* joy, Room* room, float dt){
	//determine all actions being taken
	//update hero's states to be used in animation and position updates

	if(hero->sword.active){
		UpdateSword(&hero->sword, hero->direction, hero->pos, dt);
	}else{
		hero->action = IDLE;
	}

	if(hero->knockbackTimer > 0){
		hero->knockbackTimer -= dt;
	}else{
		ReadHeroInput(hero, joy);
	}

	Enemy* attacker;
	if(hero->hitDelayTimer > 0){
		hero->hitDelayTimer -= dt;
	}else if(CheckHeroEnemyCollision(hero, room->enemies, &attacker)){
		hero->health--;
		hero->hitDelayTimer = HIT_DELAY;
		hero->knockbackTimer = KNOCKBACK_DURATION;
		ApplyKnockback(hero, attacker);
	}
	if(!CheckHeroTileCollision(hero, room->tiles, dt)){
		hero->pos = UpdatePosition(hero->pos, hero->velocity, dt);	
		UpdateHeroHitbox(&hero->hitBox, hero->pos);
	}


	if(hero->direction == SOUTH){
		hero->animator.baseX = 0 * HERO_WIDTH;
	}else if(hero->direction == WEST){
		hero->animator.baseX = 2 * HERO_WIDTH;
	}else if(hero->direction == EAST){
		hero->animator.baseX = 4 * HERO_WIDTH;
	}else if(hero->direction == NORTH){
		hero->animator.baseX = 6 * HERO_WIDTH;
	}

	if(hero->action != IDLE){Animate(&hero->animator, dt);}
	hero->animator.frameRect.x = hero->animator.baseX + hero->animator.frame * hero->animator.frameRect.width;

	if(IsKeyPressed(KEY_T)){
		hero->health++;
	}
	if(hero->health > hero->maxHealth){
		hero->health = 1;
	}
}
