#include "EntityManager.h"

EntityManager::EntityManager() {

	for (uint32_t i = 1; i <= MAX_ENTITIES; i++) {
		mEntityId.push(i);
	}
}

std::shared_ptr<Entity> EntityManager::CreateEntity() {

	auto entity = std::make_shared<Entity>(Entity(mEntityId.front()));
	mEntities.insert({ mCurrentIndex, entity });
	mEntityId.pop();
	mCurrentIndex++;
	return entity;
}

void EntityManager::DestroyEntity(Entity& entity) {

	uint32_t id = entity.GetEntityId();
	mEntities.erase(id);
	mEntityId.push(id);
}

std::shared_ptr<Entity> EntityManager::GetEntity(const uint32_t id) {
	return mEntities.at(id);
}