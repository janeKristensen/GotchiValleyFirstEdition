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
		void AddObserver(IGameObserver* observer) override;
		void RemoveObserver(IGameObserver* observer) override;
		void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) override;
	private:
		std::unordered_set<IGameObserver*> mObservers;
	};
}
