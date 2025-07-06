#pragma once
#include "Components.h"
#include "iostream"

namespace GotchiValley {

	class Entity {

	public:
		//Entity(const uint32_t& id, Transform transform, bool interactable, bool moveable) : mId(id), mTransform(transform), mInteractable(interactable), mMoveable(moveable){};
		Entity(const uint32_t id, Transform transform, bool interactable, bool moveable) : mId(id), mTransform(transform), mInteractable(interactable), mMoveable(moveable) {};
		void setTransform(Transform transform);
		Transform getTransform();
		void setState(State state);
		State& getState();
		bool isEntityAlive();
		bool isMoveable();
		virtual void onClick();
		bool isInteractive();
		void setInteractive(bool value);

	private:
		const uint32_t mId;
		Transform mTransform;
		State mEntityState{State::INITIAL};
		bool mInteractable;
		bool mMoveable;
		bool isAlive = true;
	};
}
