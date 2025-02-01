#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "Components.h"
#include "SharedObjects.h"

namespace GotchiValley {

	class UISystem : public IGameSubject {
	public:
		void Update();
		void PollEvents(std::shared_ptr<sf::RenderWindow> window);
		void AddObserver(IGameObserver* observer) override;
		void RemoveObserver(IGameObserver* observer) override;
		void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) override;
	private:
		std::unordered_set<IGameObserver*> mObservers;
	};

}



