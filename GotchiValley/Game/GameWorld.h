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
		static GameWorld& Get() {
			static GameWorld instance;
			return instance;
		}
		void Initialize();
		void Update();
		~GameWorld() override {};
		void AddObserver(IGameObserver* observer) override;
		void RemoveObserver(IGameObserver* observer) override;
		void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const override;
		void SetLevel(const std::uint32_t levelID);
		uint8_t GetColliderCount(uint32_t x, uint32_t y);

	private:
		std::list<IGameObserver*> mObservers;
		EntityManager mEntityManager;
		LevelManager mLevelManager{ std::make_shared<sf::Texture>(std::move<sf::Texture>(sf::Texture{"bg_sprite_small.png"})) };
		uint32_t mCurrentLevelId = NULL;
		Entity mLevelEntity = NULL;
		Entity mPlayer = NULL;
		Factory mFactory;
		std::array<std::array<TileNode, (SCREEN_SIZE.y / TILE_SIZE.y)>, (SCREEN_SIZE.x / TILE_SIZE.x)> mColliderMap;

		void CreateBird(std::shared_ptr<sf::Texture> texture, sf::Vector2f position, Entity& player);
		Entity CreatePlayer(std::shared_ptr<sf::Texture> texture, sf::Vector2f position, float speed);
		
	};

}

