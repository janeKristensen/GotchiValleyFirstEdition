#include "SharedObjects.h"
#include "Components.h"
#include "MovementSystem.h"
#include "SFML/Graphics.hpp"

using namespace GotchiValley;

void MovementSystem::Update() {
	
	auto controlArray = componentRegistry.GetComponentArray<Controlable>();
	for (auto i : controlArray) {

		auto transform = componentRegistry.GetComponentOfType<Transform>(i.first);
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