#pragma once
#include "movement.h"
#include "room.h"
#include "animate.h"
#include "assets.h"
#include "constants.h"
#include "common.h"
#include "tile.h"
#include <SDL3/SDL.h>
#include "sword.h"

typedef struct Hero{
	Vector2 pos;
	Vector2 velocity;
	int health;
	int maxHealth;
	Direction direction;
	Action action;
	int speed;
	Animator animator;
	Rectangle hitBox;
	float hitDelayTimer;
	Sword sword;
	float knockbackTimer;
}Hero;

void LoadHero(Hero* hero);
void ReadHeroInput(Hero* hero, SDL_Joystick* joy);
void UpdateHeroHitbox(Rectangle* hitBox, Vector2 pos);
void ApplyKnockback(Hero* hero, Enemy* attacker);
void UpdateHero(Hero* hero, SDL_Joystick* joy, Room* room, float dt);
