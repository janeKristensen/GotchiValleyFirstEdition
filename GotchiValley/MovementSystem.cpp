#include "MovementSystem.h"
#include "SFML/Graphics.hpp"

using namespace GotchiValley;

void MovementSystem::Update(ComponentManager<Transform>& transformManager, ComponentManager<Controlable>& controlManager) {
	for (uint32_t i = 0; i < MAX_ENTITIES; i++) {

		if (controlManager.HasComponent(i)) {

			auto transform = transformManager.GetComponentOfType(i);
			float acceleration = 1.f;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
				transform->velocity.y = -acceleration;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
				transform->velocity.y = acceleration;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
				transform->velocity.x = acceleration;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
				transform->velocity.x = -acceleration;
			}
		}
	}
}