#pragma once
#include <cstdint>

struct PlayerStats {
	float speed;
	std::uint16_t health;
};

struct Transform {
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f gravity;
	sf::Transform transform;
};