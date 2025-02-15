#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "Components.h"
#include "SharedObjects.h"

namespace GotchiValley {

	class AnimationSystem : public IGameObserver {
	public:
		template<typename... Args>
		AnimationSystem(Args*... args) {
		
			mGameSubjects = { static_cast<void*>(args)... };
			for (void* i : mGameSubjects) {
				IGameSubject* it = static_cast<IGameSubject*>(i);
				it->AddObserver(this);
			}
		}
		void Update(float dt);
		void OnNotify(const Entity& entity, const EntityEvent& eventMessage);
	private:
		std::unordered_set<void*> mGameSubjects;

	};
}