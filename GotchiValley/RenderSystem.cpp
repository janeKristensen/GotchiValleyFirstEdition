#include "RenderSystem.h"


using namespace GotchiValley;

void RenderSystem::Update(ComponentManager<sf::Sprite>& spriteManager, sf::RenderWindow& window) {

	for (uint32_t i = 0; i < MAX_ENTITIES; i++) {

		if (!spriteManager.HasComponent(i)) continue;
		auto sprite = spriteManager.GetComponentOfType(i);
		
		window.draw(*sprite);	
	}
}

void RenderSystem::AttachTexture(ComponentManager<sf::Texture>& textureManager, Entity entity, std::string filename) {

	auto texture = textureManager.GetComponentOfType(entity);
	if (!texture->loadFromFile(std::filesystem::absolute(filename).string()))
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

