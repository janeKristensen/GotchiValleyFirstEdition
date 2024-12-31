#include "RenderSystem.h"
#include "Components.h"

void RenderSystem::Draw(Entity entity, sf::RenderWindow& window) {

	auto vertices = *entity.GetComponentOfType<sf::VertexArray>();

	sf::RenderStates& states = *entity.GetComponentOfType<sf::RenderStates>();
	auto transform = *entity.GetComponentOfType<Transform>();
	states.transform = transform.transform;
	states.texture = &*entity.GetComponentOfType<sf::Texture>();

	window.draw(vertices, states);
	window.display();
}

void RenderSystem::LoadTexture(Entity entity, std::string filename) {

	sf::Texture& texture = *entity.GetComponentOfType<sf::Texture>();
	if (!texture.loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
}

