#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"

class RenderSystem {
public:
	void Draw(Entity entity, sf::RenderWindow& window);
	void LoadTexture(Entity entity, std::string filename);

private:

};
