#include "EntityManager.h"

using namespace GotchiValley;

EntityManager::EntityManager() {

	for (uint32_t i = 1; i <= MAX_ENTITIES; i++) {
		mEntityId.push(i);
	}
}

Entity EntityManager::CreateEntity() {

	auto entity = mEntityId.front();
	mEntityId.pop();
	mEntitiesToIndex[entity] = mCurrentIndex;
	mCurrentIndex++;
	return entity;
}

void EntityManager::DestroyEntity(Entity& entity) {

	mEntityId.push(entity);

	auto lastElement = mEntities[mCurrentIndex - 1];
	mEntities[mCurrentIndex - 1] = entity;
	mEntitiesToIndex[lastElement] = mEntitiesToIndex[entity];
	mEntities[mEntitiesToIndex[entity]] = lastElement;
	mEntitiesToIndex.erase(entity);
	mCurrentIndex--;
}

