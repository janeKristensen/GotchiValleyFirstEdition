#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "GameWorld.h"
#include "Entity.h"
#include "Creature.h"
#include "Player.h"
#include "GlobalVariables.h"
#include "Components.h"
#include "SFML/Graphics.hpp"
#include "Pathfinder.h"

namespace GotchiValley {

	class MovementSystem : public IGameSubject {
	public:
		MovementSystem(GameWorld& gameWorld) : mGameWorld(gameWorld) {};
		~MovementSystem() {};
		void update(float& dt);
		void addObserver(IGameObserver* observer) override;
		void removeObserver(IGameObserver* observer) override;
		void notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const override;
	private:
		std::unordered_set<IGameObserver*> mObservers;
		GameWorld mGameWorld;
		const float mAcceleration = 1.f;
		void setFollowPath(std::shared_ptr<Creature>& creature, const float& dt);
	};
}
