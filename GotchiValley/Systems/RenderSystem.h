#pragma once
#include "GameWorld.h"
#include "GlobalVariables.h"
#include "Components.h"
#include "SFML/Graphics.hpp"
#include "Interfaces.h"
#include "Entity.h"
#include "Creature.h"


namespace GotchiValley {

	class RenderSystem {
	public:
		RenderSystem(GameWorld& gameWorld) : mGameWorld(gameWorld) {};
		void update(sf::RenderWindow& window);
		void attachTexture(std::shared_ptr<Entity>& entity, const std::string& filename);

	private:
		GameWorld mGameWorld;
	};

}

