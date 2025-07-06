
#include "UISystem.h"

using namespace GotchiValley;


void UISystem::update(std::shared_ptr<sf::RenderWindow> window) {

	while (const std::optional event = window->pollEvent()) {

		if (event->is<sf::Event::Closed>()) {
			window->close();
		}
		else if (event->is<sf::Event::KeyPressed>()) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				window->close();
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			/*auto button = componentRegistry.GetComponentArray<Button>();

			for (auto i = button.begin(); i != button.end(); i++) {

				auto collider = componentRegistry.GetComponentOfType<Collider>(i->first);

				if (collider->boundingBox.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)))) {

					auto interactable = componentRegistry.GetComponentOfType<Interactable>(i->first);
					
					if (interactable->interactionActive) {

						i->second->OnClick();
						interactable->interactionActive = false;
					}
				}
			}*/
		}
	}
}

void UISystem::addObserver(IGameObserver* observer) {

	mObservers.emplace(observer);
}

void UISystem::removeObserver(IGameObserver* observer) {

	mObservers.erase(observer);
}

void UISystem::notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const {

	for (auto observer : mObservers) {
		observer->onNotify(entity, eventMessage);
	}
}

