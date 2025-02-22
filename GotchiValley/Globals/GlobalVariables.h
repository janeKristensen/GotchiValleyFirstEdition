#pragma once
#include <cstdint>
#include <cstddef>


namespace GotchiValley {

	using Entity = uint32_t;
	constexpr std::size_t MAX_ENTITIES{ 1000 };

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
	};

	enum class AnimationName {
		INITIAL,
		IDLE,
		RUNNING,
		COLLIDING,
		INTERACTING,
	};
}
