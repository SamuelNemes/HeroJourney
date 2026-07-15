#pragma once
#include "raylib.h"

typedef struct Assets{
	Texture2D tileSheet;
	Texture2D heroSheet;
	Texture2D goblinSheet;
	Texture2D slimeSheet;
	Texture2D menu;
	Texture2D hearts;
	Texture2D heroCloseup;
	Texture2D swordSheet;
}Assets;

void LoadAssets(Assets* assets);

void UnloadAssets(Assets* assets);
