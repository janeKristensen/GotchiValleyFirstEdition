#pragma once
#include "EntityManager.h"
#include "SFML/Graphics.hpp"

class RenderSystem {
public:
	void Draw(EntityManager& manager, sf::RenderWindow& window);
	void LoadTexture(Entity& entity, std::string filename);
	sf::Texture& LoadTexture(std::string filename);

private:

};
