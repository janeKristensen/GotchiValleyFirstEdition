#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "Components.h"
#include "SharedObjects.h"
#include "GlobalVariables.h"
#include "SFML/Graphics.hpp"

namespace GotchiValley {

	class PhysicsSystem : public IGameObserver {
	public:
		template<typename... Args>
		PhysicsSystem(Args*... args) {
			mGameSubjects = { static_cast<void*>(args)... };
			for (void* i : mGameSubjects) {
				IGameSubject* it = static_cast<IGameSubject*>(i);
				it->AddObserver(this);
			};
		}

		void Update(float& dt);
		void SetPosition(Entity & entity, sf::Vector2f & position);
		void OnNotify(const Entity & entity, const EntityEvent & eventMessage) override;
	private:
		std::unordered_set<void*> mGameSubjects;
	};
}