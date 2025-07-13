#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "Components.h"
#include "Entity.h"
#include "Interfaces.h"
#include "GlobalVariables.h"
#include "SFML/Graphics.hpp"

namespace GotchiValley {

	class GameWorld;

	class PhysicsSystem : public IGameObserver {
	public:
		template<typename... Args>
		PhysicsSystem(GameWorld& gameWorld, Args*... args ) : mGameWorld(gameWorld) {
			mGameSubjects = { static_cast<void*>(args)... };
			for (void* i : mGameSubjects) {
				IGameSubject* it = static_cast<IGameSubject*>(i);
				it->addObserver(this);
			};
		}

		void update(float& dt);
		void setPosition(std::shared_ptr<Entity>& entity, sf::Vector2f & position);
		void onNotify(std::shared_ptr<Entity>& entity, const EntityEvent & eventMessage) override;
	private:
		std::unordered_set<void*> mGameSubjects;
		GameWorld& mGameWorld;
	};
}