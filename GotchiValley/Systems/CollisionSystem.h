#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "SharedObjects.h"
#include "Components.h"

namespace GotchiValley{

	class CollisionSystem : public IGameSubject {
	public:
		~CollisionSystem() override {};
		void Update();
		void ResolveCollision(const std::pair<const Entity, const std::shared_ptr<Collider>>& entity, const std::pair<const Entity, const std::shared_ptr<Collider>>& other) const;
		void ResolveInteractions(const std::pair<const Entity, const std::shared_ptr<Collider>>& entity, const std::pair<const Entity, const std::shared_ptr<Collider>>& other) const;
		void AddObserver(IGameObserver* observer) override;
		void RemoveObserver(IGameObserver* observer) override;
		void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const override;
	private:
		std::unordered_set<IGameObserver*> mObservers;
	};
}
