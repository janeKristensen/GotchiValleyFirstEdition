
#include "RenderSystem.h"


using namespace GotchiValley;


void RenderSystem::Update(sf::RenderWindow& window) {

	auto levelVertexArray = componentRegistry.GetComponentArray<Level>();
	for (auto i = levelVertexArray.begin(); i != levelVertexArray.end(); i++) {

		sf::RenderStates states;
		states.texture = i->second->texture.get();
		window.draw(i->second->vertices, states);
	}

	auto spriteArray = componentRegistry.GetComponentArray<Sprite>();
	for (auto i = spriteArray.begin(); i != spriteArray.end(); i++) {

		window.draw(i->second->sprite);	
	}
}

void RenderSystem::AttachTexture(Entity& entity, const std::string& filename) {

	auto spriteComponent = componentRegistry.GetComponentOfType<Sprite>(entity);
	auto texture = std::make_unique<sf::Texture>();
	
	if (!texture->loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
	spriteComponent->sprite.setTexture(*texture);
	spriteComponent->texture = std::move(texture);
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

