#pragma once
#include <typeindex>
#include <unordered_map>
#include "GotchiValley.h"

extern const std::size_t MAX_ENTITIES;

class Entity {
public:
	Entity(uint32_t id) : mId(id) {}

	template <typename T>
	void AddComponent(T component) {

		mComponents[std::type_index(typeid(T))] = std::make_shared<T>(std::move(component));
	}

	template <typename T>
	void RemoveComponent() {

		mComponents.erase[std::type_index(typeid(T))];
	}

	template <typename T>
	std::shared_ptr<T> GetComponentOfType() {

		auto it = mComponents.find(std::type_index(typeid(T)));
		if (it != mComponents.end()) {
			return std::static_pointer_cast<T>(it->second);
		}

		return nullptr;
	}

	uint32_t GetEntityId() {

		return mId;
	}

private:
	const uint32_t mId;
	std::unordered_map<std::type_index, std::shared_ptr<void>> mComponents{};
};