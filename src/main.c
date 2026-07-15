#include "raylib.h"
#include <math.h>
#include "constants.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include "game.h"

int main(void){
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
	InitWindow(1280, 1024, "beta 0.4");

	ToggleFullscreen();

	RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

	SDL_Init(SDL_INIT_JOYSTICK);
	SDL_Joystick* joy = NULL;
	int count = 0;
	SDL_JoystickID* joysticks = SDL_GetJoysticks(&count);
	if(count > 0) joy = SDL_OpenJoystick(joysticks[0]);
	SDL_free(joysticks);

	Game game = {0};
	LoadGame(&game);

	while(!(WindowShouldClose())){
		SDL_Event e;
		while(SDL_PollEvent(&e));

		UpdateGame(&game, joy);

		float screenWidth = (float)GetScreenWidth();
		float screenHeight = (float)GetScreenHeight();

		float scale = fminf(screenWidth / SCREEN_WIDTH, screenHeight / SCREEN_HEIGHT);
		
		BeginTextureMode(target);
			ClearBackground(RAYWHITE);
			DrawGame(&game);
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		
		DrawTexturePro(
			target.texture, 
			(Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height}, 
			(Rectangle){
				(screenWidth - ((float)SCREEN_WIDTH * scale)) * 0.5f,
				(screenHeight - ((float)SCREEN_HEIGHT * scale)) * 0.5f,
				(float)SCREEN_WIDTH * scale,
				(float)SCREEN_HEIGHT * scale
			},
			(Vector2){0,0},
			0.0f,
			WHITE
		);

		EndDrawing();
	}

	if(joy) SDL_CloseJoystick(joy);
	SDL_Quit();

	KillGame(&game);
	UnloadRenderTexture(target);
	CloseWindow();
	return 0;
}
