#pragma once
#include  <memory>
#include <typeindex>
#include <unordered_map>
#include "EntityManager.h"

namespace GotchiValley {

	template <typename T>
	class ComponentManager {
	public:

		void AddComponent(Entity& entity, T component) {

			mComponents[entity] = std::make_shared<T>(std::move(component));
		}

		void RemoveComponent(Entity& entity) {

			mComponents.erase[entity];
		}

		bool HasComponent(Entity entity) {
			return mComponents.find(entity) != mComponents.end();
		}

		std::shared_ptr<T> GetComponentOfType(Entity& entity) {

			auto it = mComponents.find(entity);
			if (it != mComponents.end()) {
				return std::static_pointer_cast<T>(it->second);
			}

			return nullptr;
		}

	private:
		std::unordered_map<Entity, std::shared_ptr<void>> mComponents{};
	};
}