#include "Entity.h"
#include <fstream>
#include <nlohmann/json.hpp>

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

void Entity::setMoveable(bool value) {

	mMoveable = value;
}

std::string Entity::getSound(EntityEvent event) {

	return entitySounds[event];
}

void Entity::setSounds(std::string filename){

	std::ifstream file(filename);

	if (!file.is_open()) {
		throw std::runtime_error("File not found");
	}
	else {

		nlohmann::json data = nlohmann::json::parse(file);
		if (data.is_object()) {

			for (auto& [key, value] : data.items()) {

				EntityEvent event = stringToEntityEvent(key);
				std::string file = value.get<std::string>();
				entitySounds.insert(std::make_pair(event, file));
			}
		}
	}	
}