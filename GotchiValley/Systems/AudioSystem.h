#pragma once
#include "SFML/Audio.hpp"
#include "IObserver.h"
#include <queue>

namespace GotchiValley {

	class GameWorld;

	class AudioSystem : public IGameObserver {
	public:
		template<typename... Args>
		AudioSystem(GameWorld& gameWorld, Args*... args) : mGameWorld(gameWorld) {

			mGameSubjects = { static_cast<void*>(args)... };
			for (void* i : mGameSubjects) {
				IGameSubject* it = static_cast<IGameSubject*>(i);
				it->addObserver(this);
			}
		}
		void update(float dt);
		void loadSound(std::string filename);
		void onNotify(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage);
	private:
		std::unordered_set<void*> mGameSubjects;
		GameWorld& mGameWorld;
		std::unordered_map<std::string,sf::SoundBuffer> mSoundBuffers;
		std::queue<sf::Sound> mSoundQueue;

	};
}
