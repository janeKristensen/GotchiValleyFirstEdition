#pragma once
#include "GotchiValley.h"
#include <array>
#include <queue>
#include <unordered_map>

namespace GotchiValley {

	//extern const std::size_t MAX_ENTITIES;
	using Entity = uint32_t;

	class EntityManager {

	public:
		EntityManager();
		Entity CreateEntity();
		void DestroyEntity(Entity& entity);

	private:
		std::size_t mCurrentIndex{};
		std::array<Entity, MAX_ENTITIES> mEntities{};
		std::queue<uint32_t> mEntityId{};
		std::unordered_map<Entity, size_t> mEntitiesToIndex;
	};
}