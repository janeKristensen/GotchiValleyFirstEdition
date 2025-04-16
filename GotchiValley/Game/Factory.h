#pragma once
#include "GlobalVariables.h"
#include "EntityManager.h"
#include "SharedObjects.h"

namespace GotchiValley {

	class Factory {
	public:
		template<typename... Args>
		Entity CreateEntity(EntityManager& entityManager,  Args... args){

			mEntity = entityManager.CreateEntity();
			AddComponent(args...);
			return mEntity;
		}

	private:
		Entity mEntity;

		template <typename T>
		void AddComponent(const T& t) {
			componentRegistry.AddComponent(mEntity, t);
		}

		template<typename First, typename... Rest>
		void AddComponent(const First& first, const Rest&... rest) {

			componentRegistry.AddComponent(mEntity, first);
			AddComponent(rest...);
		}
	};
	
}
