#pragma once
#include "Components.h"
#include "SharedObjects.h"
#include "GlobalVariables.h"
#include "SFML/Graphics.hpp"

namespace GotchiValley {

	class PhysicsSystem {
	public:

		void Update(float& dt);
		void SetPosition(Entity& entity, sf::Vector2f& position);
	private:

	};

}