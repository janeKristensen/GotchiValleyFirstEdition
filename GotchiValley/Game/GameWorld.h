#pragma once
#include "IObserver.h"
#include "Components.h"
#include "GlobalVariables.h"
#include "ComponentRegistry.h"
#include "SharedObjects.h"
#include "EntityManager.h"
#include "LevelManager.h"
#include "SFML/Graphics.hpp"
#include "Factory.h"




namespace GotchiValley {

	class GameWorld : public IGameSubject {
	public:
		void Initialize();
		~GameWorld() override {};
		void AddObserver(IGameObserver* observer) override;
		void RemoveObserver(IGameObserver* observer) override;
		void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const override;
		void PollEvents(std::shared_ptr<sf::RenderWindow> window);
		void SetLevel(const std::uint32_t levelID);

	private:
		std::list<IGameObserver*> mObservers;
		EntityManager mEntityManager;
		LevelManager mLevelManager{ std::make_shared<sf::Texture>(std::move<sf::Texture>(sf::Texture{"bg_sprite_small.png"})) };
		uint32_t mCurrentLevelId = 0;
		Entity mCurrentLevel = NULL;
		Factory mFactory;
		
	};

}

