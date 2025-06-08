
#include "GameWorld.h"
#include "BehaviourScripts.h"

using namespace GotchiValley;

void GameWorld::Initialize() {
	
	componentRegistry.RegisterComponentManager<PlayerStats>();
	componentRegistry.RegisterComponentManager<EntityState>();
	componentRegistry.RegisterComponentManager<Transform>();
	componentRegistry.RegisterComponentManager<Moveable>();
	componentRegistry.RegisterComponentManager<Controlable>();
	componentRegistry.RegisterComponentManager<Collider>();
	componentRegistry.RegisterComponentManager<Sprite>();
	componentRegistry.RegisterComponentManager<Animation>();
	componentRegistry.RegisterComponentManager<Interactable>();
	componentRegistry.RegisterComponentManager<Button>();
	componentRegistry.RegisterComponentManager<Level>();
	componentRegistry.RegisterComponentManager<PlayerEntity>();
	componentRegistry.RegisterComponentManager<FollowBehaviour>();
	componentRegistry.RegisterComponentManager<RoamBehaviour>();
	componentRegistry.RegisterComponentManager<EvolutionState>();


	auto birdTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_sprite_sheet.png")));
	auto playerTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("sprite_sheet.png")));
	auto BigEgg = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_big.png")));

	auto newLevel = Level{ mLevelManager.LoadLevel(1) };
	mCurrentLevelId = newLevel.levelId;
	mLevelEntity = mFactory.CreateEntity(mEntityManager, newLevel);

	mPlayer = CreatePlayer(playerTexture, { 300.f, 300.f }, 80.f);
	CreateBird(birdTexture, { 400.f, 500.f }, mPlayer);
	CreateBird(birdTexture, { 200.f, 200.f }, mPlayer);

	auto button = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(BigEgg),
		Transform({ sf::Vector2f(250,150), sf::Vector2f(0,0), 80.f }),
		Collider({ sf::FloatRect({250,150}, {32,32}) }),
		Interactable()
	);
	componentRegistry.AddComponent(button,
		Button(
			[button, this]() {
				uint32_t nextLevel = mCurrentLevelId + 1;
				if(nextLevel < mLevelManager.GetNumberOfLevels()) this->SetLevel(nextLevel);
			}
		)
	);

}


void GameWorld::SetLevel(const std::uint32_t levelID) {

	componentRegistry.RemoveEntity(mLevelEntity);
	auto level { mLevelManager.LoadLevel(levelID) };
	mLevelEntity = mFactory.CreateEntity(mEntityManager, level);
	mCurrentLevelId = levelID;
}

void GameWorld::CreateBird(std::shared_ptr<sf::Texture> texture, const sf::Vector2f& position, Entity& player) {

	auto bird = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(texture),
		eggAnimation,
		Transform({ position, {0.f, 0.f}, 30.f }),
		Collider({ sf::FloatRect({position.x , position.y }, { TILE_SIZE.x - 5, TILE_SIZE.y - 5}) }),
		Interactable(),
		Moveable(),
		EntityState{ State::INITIAL },
		EvolutionState(),
		FollowBehaviour{ player },
		RoamBehaviour()
	);
	componentRegistry.AddComponent(bird,
		Button(
			[bird, this]() {

				Behaviours::EggBehaviour(bird, birdAnimation);
			}
		)
	);
}

Entity GameWorld::CreatePlayer(std::shared_ptr<sf::Texture> texture, const sf::Vector2f& position, const float& speed) {

	auto player = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(texture),
		playerAnimation,
		Transform({ position, sf::Vector2f(0,0), speed }),
		Collider({ sf::FloatRect({position.x , position.y  }, { TILE_SIZE.x , TILE_SIZE.y  }) }),
		Moveable(),
		Controlable(),
		PlayerStats(100),
		EntityState(),
		PlayerEntity()
	);

	return player;
}


void GameWorld::AddObserver(IGameObserver* observer) {

	mObservers.emplace_back(observer);
}

void GameWorld::RemoveObserver(IGameObserver* observer) {

	mObservers.remove(observer);
}

void GameWorld::NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const {
	
	for (auto observer : mObservers) {
		observer->OnNotify(entity, eventMessage);
	}
}


