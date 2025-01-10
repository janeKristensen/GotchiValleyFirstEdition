#include "RenderSystem.h"
#include "SFML/Graphics.hpp"


void RenderSystem::Draw(EntityManager& manager, sf::RenderWindow& window) {

	window.clear();

	for (uint32_t i = 0; i < MAX_ENTITIES; i++) {

		auto sprite = manager.GetComponent<sf::Sprite>(i);
		if (!sprite) {
			continue;
		}
		window.draw(*sprite);
		
	}

	window.display();
}

void RenderSystem::LoadTexture(Entity& entity, std::string filename) {

	sf::Texture& texture = *entity.GetComponentOfType<sf::Texture>();
	if (!texture.loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
}

sf::Texture& RenderSystem::LoadTexture(std::string filename) {

	sf::Texture texture;
	if (!texture.loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
	return texture;
}

