#pragma once
#include "GlobalVariables.h"
#include "Components.h"
#include "SFML/Graphics.hpp"
#include "Interfaces.h"
#include "Entity.h"



namespace GotchiValley {

	class GameWorld;

	class RenderSystem {
	public:
		RenderSystem(GameWorld& gameWorld) : mGameWorld(gameWorld) {};
		void update(sf::RenderWindow& window);
		void attachTexture(std::shared_ptr<Entity>& entity, const std::string& filename);

	private:
		GameWorld& mGameWorld;
	};

}

