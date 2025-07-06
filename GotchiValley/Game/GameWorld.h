#pragma once
#include "IObserver.h"
#include "Entity.h"
#include "Components.h"
#include "GlobalVariables.h"
#include "LevelManager.h"
#include "SFML/Graphics.hpp"
#include "Factory.h"


namespace GotchiValley {

	class GameWorld : public IGameSubject {
	public:
		void initialize();
		~GameWorld() override {};
		void addObserver(IGameObserver* observer) override;
		void removeObserver(IGameObserver* observer) override;
		void notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const override;
		void setLevel(const std::uint32_t levelID);
		Level& getCurrentLevel();
		uint32_t addEntity(std::shared_ptr<Entity>& entity);
		std::array<std::shared_ptr<Entity>, 1000> getEntities();

	private:
		std::list<IGameObserver*> mObservers;
		std::array<std::shared_ptr<Entity>, 1000> mEntityArray;
		uint32_t mCurrentArrayIndex = 0;
		LevelManager mLevelManager{ std::make_shared<sf::Texture>(std::move<sf::Texture>(sf::Texture{"bg_sprite_small.png"})) };
		Level mCurrentLevel;

	};

}

