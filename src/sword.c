#include "sword.h"
#include "constants.h"
#include <math.h>
#include <stdio.h>

void LoadSword(Sword* sword){
	sword->active = false;
	sword->swingTimer = 0;
	sword->startAngle = 0.0;
	sword->currentAngle = 0.0;
	sword->endAngle = 0.0;
	sword->point = (Vector2){-999, -999};
	sword->pos = (Vector2){-999, -999};
	sword->pivot = (Vector2){-999, -999};
	LoadAnimator(&sword->animator, 0, 0, SWORD_WIDTH, SWORD_HEIGHT, 0, SWORD_FRAME_COUNT, 0);
}

void ActivateSword(Sword* sword, Direction direction, Vector2 heroPos){
	sword->active = true;
	switch(direction){
		case NORTH:
			sword->startAngle = -PI / 4;
			sword->endAngle = -3 * PI / 4;
			sword->pivot.x = SWORD_XPIVOT_NORTH + heroPos.x;
			sword->pivot.y = SWORD_YPIVOT_NORTH + heroPos.y;
			break;
		case EAST:
			sword->startAngle = PI / 4;
			sword->endAngle = -PI / 4;
			sword->pivot.x = SWORD_XPIVOT_EAST + heroPos.x;
			sword->pivot.y = SWORD_YPIVOT_EAST + heroPos.y;
			break;
		case SOUTH:
			sword->startAngle = 3 * PI/ 4;
			sword->endAngle = PI / 4;
			sword->pivot.x = SWORD_XPIVOT_SOUTH + heroPos.x;
			sword->pivot.y = SWORD_YPIVOT_SOUTH + heroPos.y;
			break;
		case WEST:
			sword->startAngle = 5 * PI / 4;
			sword->endAngle = 3 * PI / 4;
			sword->pivot.x = SWORD_XPIVOT_WEST + heroPos.x;
			sword->pivot.y = SWORD_YPIVOT_WEST + heroPos.y;
			break;
	}
	sword->point.x = sword->pivot.x + cos(sword->currentAngle) * SWORD_LENGTH;
	sword->point.y = sword->pivot.y + sin(sword->currentAngle) * SWORD_LENGTH;
}
void UpdateSword(Sword* sword, Direction direction, Vector2 heroPos, float dt){
	sword->swingTimer += dt;
	if(sword->swingTimer >= SWORD_SWING_DURATION){
		sword->active = false;
		sword->swingTimer = 0;
		sword->point = (Vector2){-999, -999};
		sword->pivot = (Vector2){-999, -999};
		return;
	}

	sword->currentAngle = sword->startAngle + (sword->endAngle - sword->startAngle) * (sword->swingTimer / SWORD_SWING_DURATION);

	switch(direction){
		case NORTH:
			sword->pivot.x = SWORD_XPIVOT_NORTH + heroPos.x;
			sword->pivot.y = SWORD_YPIVOT_NORTH + heroPos.y;
			break;
		case EAST:
			sword->pivot.x = SWORD_XPIVOT_EAST + heroPos.x;
			sword->pivot.y = SWORD_YPIVOT_EAST + heroPos.y;
			break;
		case SOUTH:
			sword->pivot.x = SWORD_XPIVOT_SOUTH + heroPos.x;
			sword->pivot.y = SWORD_YPIVOT_SOUTH + heroPos.y;
			break;
		case WEST:
			sword->pivot.x = SWORD_XPIVOT_WEST + heroPos.x;
			sword->pivot.y = SWORD_YPIVOT_WEST + heroPos.y;
			break;
	}

	sword->point.x = sword->pivot.x + cos(sword->currentAngle) * SWORD_LENGTH;
	sword->point.y = sword->pivot.y + sin(sword->currentAngle) * SWORD_LENGTH;
}
