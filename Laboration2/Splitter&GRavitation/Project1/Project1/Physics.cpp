#include "Physics.h"

Physics::Physics() {

}

Physics::Physics(v2 position, v2 size, v2 velocity, float restitution) {
	this->position = position;
	this->size = size;
	this->velocity = velocity;
	this->restitution = restitution;
	
	speedMax = 0.5f;
	speedMin = -0.5f;

	srand(time(NULL));
}

Physics::~Physics() {

}

v2 Physics::getPosition() {
	return this->position;
}

v2 Physics::getSize() {
	return this->size;
}

v2 Physics::getVelocity() {
	return this->velocity;
}

float Physics::getRestitution() {
	return this->restitution;
}

void Physics::setPosition(v2 position) {
	this->position = position;
}

void Physics::setSize(v2 size) {
	this->size = size;
}

void Physics::setVelocity(v2 velocity) {
	this->velocity = velocity;
}

void Physics::setRestitution(float restitution) {
	this->restitution = restitution;
}

// Make ball slow down over time
void Physics::applyForce(const v2 &force) {
	velocity = velocity + force;
}

void Physics::generateRandomSpeed() {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = speedMax - speedMin;
	float rVal = random * diff;

	velocity.x = speedMax + rVal;
	velocity.y = speedMax + rVal;
}

//Collision and calculating new direction.
void Physics::update(float delta, const SDL_Rect &area) {
	generateRandomSpeed();

	position = position + velocity * delta;

	if (position.x < area.x) {
		velocity.x *= -restitution;
		position.x = area.x;
	}

	if (position.x >(area.x + area.w) - area.x) {
		velocity.x *= -restitution;
		position.x = (area.x + area.w) - area.x;
	}

	if (position.y < area.y) {
		velocity.y *= -restitution;
		position.y = area.y;
	}

	if (position.y >(area.y + area.h) - area.y) {
		velocity.y *= -restitution;
		position.y = (area.y + area.h) - area.y;
	}
}