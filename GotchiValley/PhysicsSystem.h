#pragma once
#include "GotchiValley.h"
#include "SFML/Graphics.hpp"

namespace GotchiValley {

	class PhysicsSystem {
	public:

		void Update(float& dt);
		void SetPosition(Entity& entity, sf::Vector2f& position);
	private:

	};

}