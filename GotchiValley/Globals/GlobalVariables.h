#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstddef>


namespace GotchiValley {

	using Entity = uint32_t;
	constexpr sf::Vector2i SCREEN_SIZE{ 750, 750 };
	constexpr std::size_t MAX_ENTITIES{ 1000 };
	constexpr sf::Vector2i TILE_SET_SIZE{ 3, 3 };
	constexpr sf::Vector2i TILE_SIZE{ 30, 30 };
	constexpr sf::Vector2i LEVEL_SIZE{ 25, 25};

	enum class EntityEvent {
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,
		MOVE_DOWN,
		COLLISION,
		INTERACTION,
		IDLE,
	};

	enum class State { 
		INITIAL,
		IDLE, 
		RUNNING, 
		COLLIDING,
		ATTACKING, 
		INTERACTING,
		EVOLVING,
	};

	enum class AnimationName {
		INITIAL,
		IDLE,
		RUNNING,
		COLLIDING,
		INTERACTING,
		EVOLVING,
	};
}
