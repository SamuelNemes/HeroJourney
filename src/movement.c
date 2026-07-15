#include "movement.h"

Vector2 UpdatePosition(Vector2 pos, Vector2 velocity, float dt){
	pos.x += velocity.x * dt;
	pos.y += velocity.y * dt;

	return pos;
}
