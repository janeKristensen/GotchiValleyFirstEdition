#pragma once
#include "IObserver.h"
#include "GlobalVariables.h"
#include "SFML/Graphics.hpp"


namespace GotchiValley {

	class Entity;
	class Level;
	class LevelManager;
	class Player;

	class GameWorld : public IGameSubject {
	public:
		GameWorld(LevelManager& levelManager) : mLevelManager(levelManager) {};
		GameWorld(GameWorld& gameWorld) : GameWorld(gameWorld.mLevelManager) {
			mObservers = gameWorld.mObservers,
				mEntityArray = gameWorld.mEntityArray,
				mCurrentArrayIndex = gameWorld.mCurrentArrayIndex,
				mCurrentLevel = gameWorld.mCurrentLevel,
				mPlayer = gameWorld.mPlayer;
		};
		void initialize();
		~GameWorld() override {};
		void addObserver(IGameObserver* observer) override;
		void removeObserver(IGameObserver* observer) override;
		void notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const override;
		void setLevel(const std::uint32_t levelID);
		std::shared_ptr<Level> getCurrentLevel();
		uint32_t addEntity(const std::shared_ptr<Entity>& entity);
		std::array<std::shared_ptr<Entity>, MAX_ENTITIES>& getEntities();

	private:
		std::list<IGameObserver*> mObservers;
		std::array<std::shared_ptr<Entity>, MAX_ENTITIES> mEntityArray;
		uint32_t mCurrentArrayIndex = 0;
		LevelManager& mLevelManager;
		std::shared_ptr<Level> mCurrentLevel = nullptr;
		std::shared_ptr<Player> mPlayer;
	};

}

