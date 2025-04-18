#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "SharedObjects.h"
#include "GlobalVariables.h"
#include "Components.h"
#include "SFML/Graphics.hpp"
#include "Pathfinder.h"

namespace GotchiValley {

	class MovementSystem : public IGameSubject {
	public:
		~MovementSystem() {};
		void Update(float& dt);
		void AddObserver(IGameObserver* observer) override;
		void RemoveObserver(IGameObserver* observer) override;
		void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const override;
	private:
		std::unordered_set<IGameObserver*> mObservers;
		const float mAcceleration = 1.f;
		void MoveToNode(Node actor, Node destination);
	};
}
