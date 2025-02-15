#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "SharedObjects.h"
#include "GlobalVariables.h"
#include "Components.h"
#include "SFML/Graphics.hpp"

namespace GotchiValley {

	class MovementSystem : IGameSubject {
	public:
		~MovementSystem() {};
		void Update();
		void AddObserver(IGameObserver* observer);
		void RemoveObserver(IGameObserver* observer);
		void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage);
	private:
		std::unordered_set<IGameObserver*> mObservers;
	};
}
