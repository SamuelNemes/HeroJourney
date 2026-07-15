#include "animate.h"

void LoadAnimator(Animator* animator, int x, int y, int width, int height, int frame, int frameCount, float animationRate){
	animator->frameRect.x = x;
	animator->frameRect.y = y;
	animator->frameRect.width = width;
	animator->frameRect.height = height;
	animator->frame = frame;
	animator->frameCount = frameCount;
	animator->timer = 0;
	animator->animationRate = animationRate;
}

void Animate(Animator* animator, float dt){
	animator->timer += dt;
	if(animator->timer >= animator->animationRate){
		animator->timer = 0;
		if(animator->frame >= animator->frameCount-1){
			animator->frame = 0;
		}else animator->frame++;
	}
}
