#pragma once
#include "Components.h"
#include <unordered_map>
#include "iostream"
#include <SFML/Audio.hpp>

namespace GotchiValley {

	class Entity {

	public:
		//Entity(const uint32_t& id, Transform transform, bool interactable, bool moveable) : mId(id), mTransform(transform), mInteractable(interactable), mMoveable(moveable){};
		Entity(const uint32_t id, Transform transform, bool interactable, bool moveable) : mId(id), mTransform(transform), mInteractable(interactable), mMoveable(moveable) {};
		virtual void update() = 0;
		void setTransform(Transform transform);
		Transform& getTransform();
		void setPosition(sf::Vector2f newPosition);
		void setVelocity(sf::Vector2f newVelocity);
		void setState(State state);
		State& getState();
		bool isEntityAlive();
		bool isMoveable();
		virtual void onClick();
		bool isInteractive();
		void setInteractive(bool value);
		std::string getSound(EntityEvent event);
		void setSounds(std::string filename);

	protected:
		const uint32_t mId;
		Transform mTransform;
		State mEntityState{State::INITIAL};
		bool mInteractable;
		bool mMoveable;
		bool isAlive = true;
		std::unordered_map<EntityEvent, std::string> entitySounds;
	};
}
