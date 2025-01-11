#pragma once
#include "ComponentManager.h"
#include "Components.h"
#include "SFML/Graphics.hpp"

namespace GotchiValley {

	class PhysicsSystem {
	public:

		void Update(ComponentManager<Transform>& transformManager, ComponentManager<sf::Sprite>& spriteManager, ComponentManager<Collider>& colliderManager, float dt);
		void SetPosition(ComponentManager<Transform>& transformManager, Entity entity, sf::Vector2f position);
	private:

	};

}