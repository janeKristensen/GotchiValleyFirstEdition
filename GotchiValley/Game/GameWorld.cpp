
#include "GameWorld.h"
#include "Entity.h"
#include "Components.h"
#include "LevelManager.h"
#include "Creature.h"
#include "Player.h"
#include "Animations.h"

using namespace GotchiValley;


void GameWorld::initialize() {

	auto birdTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("resources\\egg_sprite_sheet.png")));
	auto playerTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("resources\\sprite_sheet.png")));
	auto BigEgg = std::make_shared<sf::Texture>(std::move(sf::Texture("resources\\egg_big.png")));

	setLevel(1);
	mPlayer = std::make_shared<Player>(Player(mCurrentArrayIndex, Transform{ {100.0f, 100.0f }, {0.0f, 0.0f}, 200.0f }, playerAnimation, playerTexture, true, true));
	addEntity(std::dynamic_pointer_cast<Entity>(mPlayer));
	mPlayer->initialize();
	mPlayer->setSounds("resources\\playerSound.json");

	auto creatureBehaviour = std::make_shared<FollowBehaviour>(mPlayer, std::vector<std::shared_ptr<Node>>{});
	auto creature = std::make_shared<Creature>(mCurrentArrayIndex, Transform{ {200.0f, 200.0f }, {0.0f, 0.0f}, 50.0f }, birdAnimation, birdTexture, creatureBehaviour);
	addEntity(std::dynamic_pointer_cast<Entity>(creature));
	creature->initialize();
	creature->setSounds("resources\\playerSound.json");
}

std::array<std::shared_ptr<Entity>, MAX_ENTITIES>& GameWorld::getEntities() {

	return mEntityArray;
}

uint32_t GameWorld::addEntity(const std::shared_ptr<Entity>& entity) {

	mEntityArray[mCurrentArrayIndex] = entity;
	mCurrentArrayIndex++;
	return mCurrentArrayIndex;
}

void GameWorld::setLevel(const std::uint32_t levelID) {

	mCurrentLevel = std::make_shared<Level>(Level{ mLevelManager.loadLevel(levelID) });
}

std::shared_ptr<Level> GameWorld::getCurrentLevel() {

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


