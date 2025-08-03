
#include "UISystem.h"
#include "GameWorld.h"
#include "Interfaces.h"

using namespace GotchiValley;


void UISystem::update(std::shared_ptr<sf::RenderWindow> window) {

	while (const std::optional uiEvent = window->pollEvent()) {

		if (uiEvent->is<sf::Event::Closed>()) {
			window->close();
		}
		else if (uiEvent->is<sf::Event::KeyPressed>()) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				window->close();
			}
		}
		else if (uiEvent->is<sf::Event::MouseButtonReleased>() && 
			uiEvent->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left) {

			std::array<std::shared_ptr<Entity>, MAX_ENTITIES>& entityArray = mGameWorld.getEntities();
			for (auto i = 0; i < entityArray.size(); i++) {

				if (entityArray[i] == nullptr) break;
				if (!entityArray[i]->isEntityAlive() || !entityArray[i]->isInteractive()) continue;

				auto entity = std::dynamic_pointer_cast<Collidable>(entityArray[i]);
				sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
				if (entity->getCollider().boundingBox.contains(mousePos)){

					entityArray[i]->onClick();
				}
			}
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

