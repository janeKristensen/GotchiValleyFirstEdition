#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "Components.h"
#include <iostream>


namespace GotchiValley {

	class UISystem : public IGameSubject {
	public:
		void update(std::shared_ptr<sf::RenderWindow> window);
		void addObserver(IGameObserver* observer) override;
		void removeObserver(IGameObserver* observer) override;
		void notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const override;
	private:
		std::unordered_set<IGameObserver*> mObservers;
	};

}



