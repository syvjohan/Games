#include "Physics.h"

Physics::Physics() {

}

Physics::Physics(v2 position, v2 size, v2 velocity, float restitution) {
	this->position = position;
	this->size = size;
	this->velocity = velocity;
	this->restitution = restitution;
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

void Physics::applyForce(const v2 &force) {
	velocity = velocity + force;
}

void Physics::update(float delta, const SDL_Rect &area) {
	position = position + velocity * delta;

	if (position.x < area.x) {
		velocity.x *= -restitution;
		position.x = area.x;
	}

	if (position.x >(area.x + area.w) - size.x) {
		velocity.x *= -restitution;
		position.x = (area.x + area.w) - size.x;
	}

	if (position.y < area.y) {
		velocity.y *= -restitution;
		position.y = area.y;
	}

	if (position.y >(area.y + area.h) - size.y) {
		velocity.y *= -restitution;
		position.y = (area.y + area.h) - size.y;
	}
}