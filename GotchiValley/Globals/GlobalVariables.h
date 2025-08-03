#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstddef>
#include <mutex>


namespace GotchiValley {

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

	inline EntityEvent stringToEntityEvent(const std::string& str) {
		if (str == "EntityEvent::COLLISION") return EntityEvent::COLLISION;
		else if (str == "EntityEvent::INTERACTION") return EntityEvent::INTERACTION;
		else if (str == "EntityEvent::IDLE") return EntityEvent::IDLE;
		else if (str == "EntityEvent::MOVE_LEFT") return EntityEvent::MOVE_LEFT;
		else if (str == "EntityEvent::MOVE_RIGHT") return EntityEvent::MOVE_RIGHT;
		else if (str == "EntityEvent::MOVE_UP") return EntityEvent::MOVE_UP;
		else if (str == "EntityEvent::MOVE_DOWN") return EntityEvent::MOVE_DOWN;
	}

	enum class State { 
		INITIAL,
		IDLE, 
		RUNNING, 
		COLLIDING,
		ATTACKING, 
		INTERACTING,
	};

	enum class CreaturePhase {
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
