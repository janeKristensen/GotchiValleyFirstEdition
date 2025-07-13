#include "Entity.h"


using namespace GotchiValley;


void Entity::setTransform(Transform transform) {

	mTransform = transform;
}

Transform& Entity::getTransform() {

	return mTransform;
}

void Entity::setPosition(sf::Vector2f newPosition) {

	mTransform.position = newPosition;
}

void Entity::setVelocity(sf::Vector2f newVelocity) {

	mTransform.velocity = newVelocity;
}

State& Entity::getState() {

	return mEntityState;
}

void Entity::setState(State state){

	mEntityState = state;
}

bool Entity::isEntityAlive() {

	return isAlive;
}

void Entity::onClick() {

	std::cout << "Entity clicked" << std::endl;
}

bool Entity::isInteractive() {

	return mInteractable;
}

void Entity::setInteractive(bool value) {

	mInteractable = value;
}

bool Entity::isMoveable() {

	return mMoveable;
}