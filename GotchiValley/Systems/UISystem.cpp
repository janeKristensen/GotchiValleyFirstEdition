
#include "UISystem.h"
#include <iostream>
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
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			auto button = componentRegistry.GetComponentArray<Button>();

			for (auto i = button.begin(); i != button.end(); i++) {

				auto collider = componentRegistry.GetComponentOfType<Collider>(i->first);

				if (collider->boundingBox.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)))) {

					auto interactable = componentRegistry.GetComponentOfType<Interactable>(i->first);
					
					if (interactable->interactionActive) {

						i->second->OnClick();
						this->NotifyObservers(i->first, EntityEvent::INTERACTION);
						interactable->interactionActive = false;
					}
				}
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

void UISystem::NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const {

	for (auto observer : mObservers) {
		observer->OnNotify(entity, eventMessage);
	}
}

