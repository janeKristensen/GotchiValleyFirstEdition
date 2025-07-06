
#include "GameWorld.h"


using namespace GotchiValley;

void GameWorld::initialize() {

	auto birdTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_sprite_sheet.png")));
	auto playerTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("sprite_sheet.png")));
	auto BigEgg = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_big.png")));

	setLevel(1);
}

std::array<std::shared_ptr<Entity>, 1000> GameWorld::getEntities() {

	return mEntityArray;
}

uint32_t GameWorld::addEntity(std::shared_ptr<Entity>& entity) {

	mEntityArray[mCurrentArrayIndex] = entity;
	mCurrentArrayIndex++;
	return mCurrentArrayIndex;
}

void GameWorld::setLevel(const std::uint32_t levelID) {

	mCurrentLevel = Level{ mLevelManager.loadLevel(levelID) };
}

Level& GameWorld::getCurrentLevel() {

	return mCurrentLevel;
}


void GameWorld::addObserver(IGameObserver* observer) {

	mObservers.emplace_back(observer);
}

void GameWorld::removeObserver(IGameObserver* observer) {

	mObservers.remove(observer);
}

void GameWorld::notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const {
	
	for (auto observer : mObservers) {
		observer->onNotify(entity, eventMessage);
	}
}


