#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "SharedObjects.h"
#include "Components.h"

namespace GotchiValley{

	struct CollisionData {
		const Entity& entity;
		std::shared_ptr<Collider>& entityCollider;
		const Entity& other;
		std::shared_ptr<Collider>& otherCollider;
	};

	class CollisionSystem : public IGameSubject {
	public:
		~CollisionSystem() override {};
		void Update();
		void ResolveCollision(const std::vector<CollisionData>& collisions) const;
		void ResolveInteractions(const Entity& entity, const std::shared_ptr<Collider>& entityCollider, const Entity& other, const std::shared_ptr<Collider>& otherCollider) const;
		void AddObserver(IGameObserver* observer) override;
		void RemoveObserver(IGameObserver* observer) override;
		void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const override;
	private:
		std::unordered_set<IGameObserver*> mObservers;
	};
}
