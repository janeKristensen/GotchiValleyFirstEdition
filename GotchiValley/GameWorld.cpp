#include "GameWorld.h"
#include "Components.h"



void GameWorld::AddObserver(IObserver* observer){
	
	mObservers.emplace_back(observer);
}

void GameWorld::RemoveObserver(IObserver* observer) {
	
	mObservers.remove(observer);
}

void GameWorld::NotifyObservers(EntityManager& manager, const sf::Event& event, std::string message) {
	
	for (auto observer : mObservers) {
		observer->OnNotify(manager, event, message);
	}
}


void GameWorld::PollEvents(EntityManager& manager, std::shared_ptr<sf::RenderWindow> window) {

	while (const std::optional event = window->pollEvent()) {

		NotifyObservers(manager, event.value(), "");
	}
}

