#pragma once

#include "raylib.h"
#include "common.h"
#include "constants.h"
#include "animate.h"
#include "movement.h"
#include "goblin.h"
#include "slime.h"
#include "assets.h"

typedef enum{
	GOBLIN,
	SLIME
}enemyType;

typedef struct Enemy Enemy;

struct Enemy{
	bool active;

	enemyType type;
	Vector2 origin;
	Texture2D* enemySheet;

	union{
		Goblin goblin;
		Slime slime;
	}as;

	void (*update)(Enemy* enemy, Tile tiles[ROOM_ROWS][ROOM_COLS], Vector2 heroPos, float dt);

	int health;
	Vector2 pos;
	Vector2 velocity;
	Direction direction;
	Action action;
	int speed;
	Animator animator;
	Rectangle hitBox;
};

void LoadEnemy(Enemy* enemy, Assets* assets, int type, int x, int y);
void UpdateEnemy(Enemy enemies[MAX_ENEMIES], Tile tiles[ROOM_ROWS][ROOM_COLS], Vector2 heroPos, Vector2 swordPos, Vector2 swordPivot, float dt);
