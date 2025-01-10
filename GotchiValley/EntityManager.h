#pragma once
#include "Entity.h"
#include "GotchiValley.h"
#include <queue>

extern const std::size_t MAX_ENTITIES;

class EntityManager {

public:
	EntityManager();
	std::shared_ptr<Entity> CreateEntity();
	void DestroyEntity(Entity& entity);
	std::shared_ptr<Entity> GetEntity(const uint32_t id);

	template <typename T>
	void AddComponent(Entity& entity, T component) {
		entity.AddComponent(component);
	}

	template <typename T>
	void RemoveComponent(Entity& entity) {
		entity.RemoveComponent();
	}

	template <typename T>
	bool HasComponent(const uint32_t id) {

		if (id >= mCurrentIndex) return false;
		auto& entity = mEntities.at(id);
		return (entity->GetComponentOfType<T>() != nullptr);
	}

	template <typename T>
	std::shared_ptr<T> GetComponent(const uint32_t id) {

		if (id >= mCurrentIndex) return nullptr;
		auto& entity = mEntities.at(id);
		return entity->GetComponentOfType<T>();
	}

private:
	std::size_t mCurrentIndex{};
	std::unordered_map<uint32_t, std::shared_ptr<Entity>> mEntities;
	std::queue<uint32_t> mEntityId{};
	
};