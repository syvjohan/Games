#include "SplitterParticle.h"

float r() {
	return ((rand() & 100) / 50.0f) - 1.0f;
}

SplitterParticle::SplitterParticle() {
	x = 500;
	y = 150;
	
	w = SIZE;
	h = SIZE;

	position.x = x;
	position.y = y;

	size.x = w;
	size.y = h;

	velocity.x = r();
	velocity.y = r();

	velocity.normalize();
	
	velocity = velocity * (((r() + 2.0f) / 2.0f) * 5 + 5);

	printf("(%.2f, %.2f)\n", velocity.x, velocity.y);
}

SplitterParticle::~SplitterParticle() {}

void SplitterParticle::update(float dt, SDL_Rect area) {
	//acceleration.y = 1.f;
	//acceleration.x = 0;

	velocity.y += 5.5f * dt; //gravity.

	velocity = velocity * 0.9999f;

	position = position + velocity * dt;
}

//float SplitterParticle::generateRandomNumber(float min, float max) {
//	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
//}
