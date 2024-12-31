#pragma once
#include "Entity.h"
#include "GotchiValley.h"
#include <queue>


class EntityManager {

public:
	EntityManager();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void Update(Entity entity, float dt);

private:
	std::size_t mCurrentIndex{};
	std::unordered_map<uint32_t, Entity> mEntities;
	std::queue<uint32_t> mEntityId{};
	
};