#pragma once
#include "IObserver.h"
#include "Components.h"
#include "GlobalVariables.h"
#include "ComponentRegistry.h"
#include "SharedObjects.h"
#include "EntityManager.h"
#include "SFML/Graphics.hpp"



namespace GotchiValley {

	class GameWorld : public ISubject {
	public:
		void Initialize();
		~GameWorld() override {} ;
		void AddObserver(IObserver* observer) override;
		void RemoveObserver(IObserver* observer) override;
		void NotifyObservers(const sf::Event& event, const std::string& message) override;
		void PollEvents(std::shared_ptr<sf::RenderWindow> window);

	private:
		std::list<IObserver*> mObservers;
	};

}

