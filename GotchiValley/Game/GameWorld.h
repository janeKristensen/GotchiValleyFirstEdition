#pragma once
#include "IObserver.h"
#include "Components.h"
#include "GlobalVariables.h"
#include "ComponentRegistry.h"
#include "SharedObjects.h"
#include "EntityManager.h"
#include "SFML/Graphics.hpp"
#include "Factory.h"




namespace GotchiValley {

	class GameWorld : public IWindowSubject {
	public:
		void Initialize();
		~GameWorld() override {};
		void AddObserver(IWindowObserver* observer) override;
		void RemoveObserver(IWindowObserver* observer) override;
		void NotifyObservers(const sf::Event& event, const std::string& message) const override;
		void PollEvents(std::shared_ptr<sf::RenderWindow> window);

	private:
		std::list<IWindowObserver*> mObservers;
	};

}

