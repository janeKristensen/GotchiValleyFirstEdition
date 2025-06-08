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
		UNEVOLVED,
		EVOLVED,
	};

	enum class AnimationName {
		INITIAL,
		IDLE,
		RUNNING,
		COLLIDING,
		INTERACTING,
		EVOLVING,
	};

	struct Node {
		int32_t y;
		int32_t x;
		int32_t parentX;
		int32_t parentY;
		float gCost;
		float hCost;
		float fCost;
		bool walkable = true;
	};

	struct TileNode {
		int32_t y;
		int32_t x;
		int32_t count = 0;
	};

	extern std::array<std::array<std::shared_ptr<Node>, (SCREEN_SIZE.y / TILE_SIZE.y)>, (SCREEN_SIZE.x / TILE_SIZE.x)> allMap;

}
