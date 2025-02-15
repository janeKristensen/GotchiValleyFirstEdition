#pragma once
#include "GlobalVariables.h"
#include "ComponentManager.h"
#include <unordered_map>
#include <memory>
#include <typeindex>


namespace GotchiValley {

	class ComponentRegistry {
	public:

		template <typename T>
		void RegisterComponentManager() {

			mManagers[std::type_index(typeid(T))] = std::make_shared<ComponentManager<T>>(std::move(ComponentManager<T>()));
		}

		template <typename T>
		void AddComponent(Entity entity, T component) {

			auto it = mManagers.find(std::type_index(typeid(T)));
			if (it != mManagers.end()) {

				ComponentManager<T>* componentManager = static_cast<ComponentManager<T>*>(it->second.get());
				componentManager->AddComponent(entity, component);
			}
		}

		template <typename T>
		void RemoveComponent() {
			mManagers.erase[std::type_index(typeid(T))];
		}

		template <typename T>
		bool HasComponent(Entity entity) {
		
			auto it = mManagers.find(std::type_index(typeid(T)));
			if (it != mManagers.end()) {

				ComponentManager<T>* componentManager = static_cast<ComponentManager<T>*>(it->second.get());
				return componentManager->HasComponent(entity);
			}

			return false;
		}

		template <typename T>
		std::shared_ptr<T> GetComponentOfType(Entity entity) {
		
			auto it = mManagers.find(std::type_index(typeid(T)));
			if (it != mManagers.end()) {

				ComponentManager<T>* componentManager = static_cast<ComponentManager<T>*>(it->second.get());
				return componentManager->GetComponentOfType(entity);
			}
			return nullptr;
		}

		template <typename T>
		std::unordered_map<Entity, std::shared_ptr<T>> GetComponentArray() {
		
			auto it = mManagers.find(std::type_index(typeid(T)));
			if (it != mManagers.end()) {

				ComponentManager<T>* componentManager = static_cast<ComponentManager<T>*>(it->second.get());
				return componentManager->GetComponentArray();
			}	
			return {};
		}


	private:
		inline static std::unordered_map<std::type_index, std::shared_ptr<void>> mManagers;
	};

}

