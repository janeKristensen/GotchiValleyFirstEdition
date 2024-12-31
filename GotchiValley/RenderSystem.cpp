#include "RenderSystem.h"

void RenderSystem::Draw(Entity entity, sf::RenderWindow& window) {

	auto sprite = *entity.GetComponentOfType<sf::Sprite>();
	auto transform = *entity.GetComponentOfType<sf::Transform>();
	window.draw(sprite, transform);
	window.display();
}