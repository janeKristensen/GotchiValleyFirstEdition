#include "EntityManager.h"

EntityManager::EntityManager() {

	for (uint32_t i = 1; i <= MAX_ENTITIES; i++) {
		mEntityId.push(i);
	}
}

Entity EntityManager::CreateEntity() {

	Entity entity = Entity(mEntityId.front());
	mEntities.insert({ mCurrentIndex, entity });
	mEntityId.pop();
	mCurrentIndex++;
	return entity;
}

void EntityManager::DestroyEntity(Entity entity) {

	uint32_t id = entity.GetEntityId();
	mEntities.erase(id);
	mEntityId.push(id);
}

void EntityManager::Update(Entity entity, float dt) {
	
	
}