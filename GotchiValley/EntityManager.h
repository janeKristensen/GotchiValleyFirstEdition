#pragma once
#include "GotchiValley.h"
#include <array>
#include <queue>
#include <unordered_map>



namespace GotchiValley {

	class EntityManager {

	public:
		EntityManager();
		Entity CreateEntity();
		void DestroyEntity(Entity& entity);

	private:
		std::queue<Entity> mEntityId{};

		/*std::size_t mCurrentIndex{};
		std::array<Entity, MAX_ENTITIES> mEntities{};
		std::unordered_map<Entity, size_t> mEntitiesToIndex;*/
	};
}