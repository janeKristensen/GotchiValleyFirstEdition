
#include "UISystem.h"

using namespace GotchiValley;

void UISystem::Update() {

}


void UISystem::PollEvents(std::shared_ptr<sf::RenderWindow> window) {

	while (const std::optional event = window->pollEvent()) {

		if (event->is<sf::Event::Closed>()) {
			window->close();
		}
		else if (event->is<sf::Event::KeyPressed>()) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				window->close();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {

				NotifyObservers(NULL, EntityEvent::INTERACTION);
			}
		}
	}
}

void UISystem::AddObserver(IGameObserver* observer) {

	mObservers.emplace(observer);
}

void UISystem::RemoveObserver(IGameObserver* observer) {

	mObservers.erase(observer);
}

void UISystem::NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) {

	for (auto observer : mObservers) {
		observer->OnNotify(entity, eventMessage);
	}
}

