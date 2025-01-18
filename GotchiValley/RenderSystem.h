#pragma once
#include "GlobalVariables.h"
#include "SharedObjects.h"
#include "Components.h"
#include "SFML/Graphics.hpp"


namespace GotchiValley {

	class RenderSystem {
	public:
		void Update(sf::RenderWindow& window);
		void AttachTexture(Entity& entity, const std::string& filename);
		//sf::Texture& LoadTexture(const std::string& filename);

	private:

	};

}

