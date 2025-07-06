#pragma once
#include <unordered_set>
#include "GameWorld.h"
#include "IObserver.h"
#include "Components.h"
#include "Player.h"
#include "Creature.h"

namespace GotchiValley{

	struct CollisionData {
		std::shared_ptr<Entity> entity;
		Collider& entityCollider;
		std::shared_ptr<Entity> other;
		Collider& otherCollider;
	};

	class CollisionSystem : public IGameSubject {
	public:
		CollisionSystem(GameWorld& gameWorld) : mGameWorld(gameWorld) {};
		~CollisionSystem() override {};
		void update();
		void resolveCollision(std::vector<CollisionData>& collisions);
		void addObserver(IGameObserver* observer) override;
		void removeObserver(IGameObserver* observer) override;
		void notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const override;
	private:

		std::unordered_set<IGameObserver*> mObservers;
		GameWorld& mGameWorld;
		std::vector<CollisionData> mCollisions;

		
	};
}
