#pragma once
#include <unordered_set>
#include "GameWorld.h"
#include "Entity.h"
#include "IObserver.h"
#include "Interfaces.h"
#include "Components.h"


namespace GotchiValley {

	class AnimationSystem : public IGameObserver {
	public:
		template<typename... Args>
		AnimationSystem(GameWorld& gameWorld, Args*... args) : mGameWorld(gameWorld) {
		
			mGameSubjects = { static_cast<void*>(args)... };
			for (void* i : mGameSubjects) {
				IGameSubject* it = static_cast<IGameSubject*>(i);
				it->addObserver(this);
			}
		}
		void update(float dt);
		void onNotify(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage);
	private:
		std::unordered_set<void*> mGameSubjects;
		GameWorld& mGameWorld;
	};
}