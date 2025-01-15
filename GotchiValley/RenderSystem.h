#pragma once
#include "GotchiValley.h"
#include "SFML/Graphics.hpp"


namespace GotchiValley {

	class RenderSystem {
	public:
		void Update(sf::RenderWindow& window);
		void AttachTexture(Entity& entity, const std::string& filename);
		sf::Texture& LoadTexture(const std::string& filename);

	private:

	};

}

