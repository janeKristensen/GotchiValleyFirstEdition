#include "RenderSystem.h"


using namespace GotchiValley;

void RenderSystem::Update(ComponentManager<sf::Sprite>& spriteManager, sf::RenderWindow& window) {

	auto spriteArray = spriteManager.GetComponentArray();

	for (auto i = spriteArray.begin(); i != spriteArray.end(); i++) {

		window.draw(*i->second);	
	}
}

void RenderSystem::AttachTexture(ComponentManager<sf::Texture>& textureManager, Entity& entity, const std::string& filename) {

	auto texture = textureManager.GetComponentOfType(entity);
	if (!texture->loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
}

sf::Texture& RenderSystem::LoadTexture(const std::string& filename) {

	sf::Texture texture;
	if (!texture.loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
	return texture;
}

