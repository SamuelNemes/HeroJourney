#pragma once

#include "raylib.h"

typedef struct Animator{
	int baseX;
	Rectangle frameRect;
	int frame;
	int frameCount;
	float timer;
	float animationRate;	//The rate (in seconds) for each frame. Float type allows for sub-second intervals
}Animator;

void LoadAnimator(Animator* animator, int x, int y, int width, int height, int frame, int frameCount, float animationRate);

void Animate(Animator* animator, float dt);
