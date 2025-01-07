#include "GameWorld.h"



void GameWorld::AddObserver(IObserver* observer){
	
	mObservers.emplace_back(observer);
}

void GameWorld::RemoveObserver(IObserver* observer) {
	
	mObservers.remove(observer);
}

void GameWorld::NotifyObservers(Entity& entity, const sf::Event& event) {
	
	for (auto observer : mObservers) {
		observer->OnNotify(entity, event);
	}
}


void GameWorld::PollEvents(Entity& entity, std::shared_ptr<sf::RenderWindow> window) {

	while (const std::optional event = window->pollEvent()) {

		NotifyObservers(entity, event.value());
	}
}