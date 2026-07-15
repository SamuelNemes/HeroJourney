#pragma once
#include "assets.h"
#include "hero.h"
#include "map.h"
#include "raylib.h"
typedef enum{
	MENU,
	ALIVE,
	DEAD,
	WIN
}gameState;

typedef struct Game{
	gameState state;
	float tick;
	Assets assets;
	Map map;
	Hero hero;	
}Game;

void LoadGame(Game* game);

void UpdateGame(Game* game, SDL_Joystick* joy);

void DrawGame(Game* game);

void KillGame(Game* game);
