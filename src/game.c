#include "game.h"
#include "room.h"
#include "movement.h"
#include "render.h"
#include "collision.h"
#include <stdio.h>


void LoadGame(Game* game){

	SetTargetFPS(120);
	LoadAssets(&game->assets);
	LoadHero(&game->hero);	
	LoadMap(&game->map, &game->assets);
}

void UpdateGame(Game* game, SDL_Joystick* joy){
	float dt = GetFrameTime();

	CheckTransition(&game->map, game->hero.pos);
	if(game->map.transitioner.flag){
		UpdateTransition(&game->map, &game->hero, dt);
		return;
	}
	UpdateHero(&game->hero, joy, game->map.currentRoom, dt);

	UpdateEnemy(game->map.currentRoom->enemies, game->map.currentRoom->tiles, game->hero.pos, game->hero.sword.point, game->hero.sword.pivot, dt);
}

void DrawGame(Game* game){


	if(game->map.transitioner.flag){
		DrawMapTransition(&game->map, game->assets.tileSheet);
		DrawHeroTransition(&game->hero, game->assets.heroSheet, game->map.transitioner.offset, game->map.transitioner.direction);
		DrawMenu(game->hero.health, game->hero.maxHealth, game->assets.menu, game->assets.hearts, game->assets.heroCloseup);

		return;
	}

	DrawMap(&game->map, game->assets.tileSheet);
	DrawHero(&game->hero, game->assets.heroSheet, game->assets.swordSheet);
	DrawMenu(game->hero.health, game->hero.maxHealth, game->assets.menu, game->assets.hearts, game->assets.heroCloseup);

}

void KillGame(Game* game){
	return;
}
