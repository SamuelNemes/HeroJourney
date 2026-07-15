#pragma once
#include "raylib.h"
#include "animate.h"
#include "common.h"

typedef struct Sword{
	bool active;
	float swingTimer;
	float startAngle;
	float currentAngle;
	float endAngle;
	Vector2 point;
	Vector2 pos;
	Vector2 pivot;
	Animator animator;
}Sword;

void LoadSword(Sword* sword);

void ActivateSword(Sword* sword, Direction direction, Vector2 heroPos);

void UpdateSword(Sword* sword, Direction direction, Vector2 heroPos, float dt);
