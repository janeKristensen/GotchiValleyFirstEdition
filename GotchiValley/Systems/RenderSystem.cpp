
#include "RenderSystem.h"


using namespace GotchiValley;


void RenderSystem::Update(sf::RenderWindow& window) {

	auto spriteArray = componentRegistry.GetComponentArray<Sprite>();
	for (auto i = spriteArray.begin(); i != spriteArray.end(); i++) {

		window.draw(i->second->sprite);	
	}
}

void RenderSystem::AttachTexture(Entity& entity, const std::string& filename) {

	auto spriteComponent = componentRegistry.GetComponentOfType<Sprite>(entity);
	auto sprite = spriteComponent->sprite;
	sf::Texture texture;
	
	if (!texture.loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
	sprite.setTexture(texture);
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

