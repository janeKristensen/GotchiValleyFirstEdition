#pragma once
#include "ComponentManager.h"
#include "Components.h"
#include "SFML/Graphics.hpp"


namespace GotchiValley {

	class RenderSystem {
	public:
		void Update(ComponentManager<sf::Sprite>& spriteManager, sf::RenderWindow& window);
		void AttachTexture(ComponentManager<sf::Texture>& textureManager, Entity& entity, const std::string& filename);
		sf::Texture& LoadTexture(const std::string& filename);

	private:

	};

}

