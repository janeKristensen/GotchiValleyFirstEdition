
#include "GameWorld.h"
#include "Components.h"

using namespace GotchiValley;

void GameWorld::AddObserver(IObserver* observer){
	
	mObservers.emplace_back(observer);
}

void GameWorld::RemoveObserver(IObserver* observer) {
	
	mObservers.remove(observer);
}

void GameWorld::NotifyObservers(const sf::Event& event, const std::string& message) {
	
	for (auto observer : mObservers) {
		observer->OnNotify(event, message);
	}
}


void GameWorld::PollEvents(std::shared_ptr<sf::RenderWindow> window) {

	while (const std::optional event = window->pollEvent()) {

		NotifyObservers(event.value(), "");
	}
}

