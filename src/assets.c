#include "assets.h"

void LoadAssets(Assets* assets){
	assets->tileSheet = LoadTexture("assets/tileSheet.png");
	assets->heroSheet = LoadTexture("assets/heroSheet.png");
	assets->goblinSheet = LoadTexture("assets/goblinSheet.png");
	assets->slimeSheet = LoadTexture("assets/slimeSheet.png");
	assets->menu = LoadTexture("assets/menu.png");
	assets->hearts = LoadTexture("assets/hearts.png");
	assets->heroCloseup = LoadTexture("assets/heroCloseup.png");
	assets->swordSheet = LoadTexture("assets/swordSheet.png");
}

void UnloadAssets(Assets* assets){
	UnloadTexture(assets->tileSheet);
	UnloadTexture(assets->heroSheet);
	UnloadTexture(assets->goblinSheet);
	UnloadTexture(assets->slimeSheet);
	UnloadTexture(assets->menu);
	UnloadTexture(assets->hearts);
	UnloadTexture(assets->heroCloseup);
	UnloadTexture(assets->swordSheet);
}
