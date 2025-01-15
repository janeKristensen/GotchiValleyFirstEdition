
#include "RenderSystem.h"
#include "SharedObjects.h"


using namespace GotchiValley;

void RenderSystem::Update(sf::RenderWindow& window) {

	auto spriteArray = componentRegistry.GetComponentArray<sf::Sprite>();

	for (auto i = spriteArray.begin(); i != spriteArray.end(); i++) {

		window.draw(*i->second);	
	}
}

void RenderSystem::AttachTexture(Entity& entity, const std::string& filename) {

	auto texture = componentRegistry.GetComponentOfType<sf::Texture>(entity);
	if (!texture->loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
}

//sf::Texture& RenderSystem::LoadTexture(const std::string& filename) {
//
//	sf::Texture texture;
//	if (!texture.loadFromFile(std::filesystem::absolute(filename).string()))
//	{
//		throw std::runtime_error("Could not load image.png");
//	}
//	return texture;
//}

