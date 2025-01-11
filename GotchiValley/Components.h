#pragma once
#include "SFML/Graphics.hpp"
#include <cstdint>

namespace GotchiValley {

	struct PlayerStats {
		std::uint16_t health;
	};

	struct Transform {
		sf::Vector2f position;
		sf::Vector2f velocity;
		float speed = 0.f;
	};

	struct Controlable {
		bool controlable = true;
	};

	struct Collider {
		sf::FloatRect boundingBox;
	};

	struct Moveable {};
}




