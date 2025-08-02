#include "AudioSystem.h"


using namespace GotchiValley;

void AudioSystem::update(float dt) {

	while (!mSoundQueue.empty()) {

		if (mSoundQueue.front().getStatus() == sf::Sound::Status::Stopped) {
			
			mSoundQueue.pop();
		}
		else {
			break;
		}
	}
}

void AudioSystem::loadSound(std::string filename){

	if (mSoundBuffers.count(filename) == 0) {

		sf::SoundBuffer buffer;
		bool success = buffer.loadFromFile(filename);
		if (success) {

			std::cout << "Sound loaded sucessfully" << std::endl;
			mSoundBuffers[filename] = std::move(buffer);
		}
		else {

			std::cout << "Failed to load sound" << std::endl;
			return;
		}
	}
	
	sf::Sound sound(mSoundBuffers.find(filename)->second);
	mSoundQueue.push(std::move(sound));
	mSoundQueue.back().play();
}

void AudioSystem::onNotify(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) {

		std::string filename = entity->getSound(eventMessage);
		loadSound(filename);
}