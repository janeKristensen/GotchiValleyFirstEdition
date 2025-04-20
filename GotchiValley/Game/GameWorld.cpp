
#include "GameWorld.h"
#include "Animations.h"


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
				this->SetLevel(mCurrentLevelId + 1);
			}
		)
	);

}

void GameWorld::Update() {

	for (auto x = 0; x < (SCREEN_SIZE.x / TILE_SIZE.x); x++) {
		for (auto y = 0; y < (SCREEN_SIZE.y / TILE_SIZE.y); y++) {

			mColliderMap[x][y].count = 0;
		}
	}
	auto colliderArray = componentRegistry.GetComponentArray<Collider>();

	auto entityLevel = componentRegistry.GetComponentOfType<Level>(mLevelEntity);
	for (auto i = entityLevel->colliders.begin(); i != entityLevel->colliders.end(); i++) {

		int32_t tempX = i->get()->boundingBox.position.x / TILE_SIZE.x;
		int32_t tempY = i->get()->boundingBox.position.y / TILE_SIZE.y;

		mColliderMap[tempX][tempY].count += 1;
		mColliderMap[tempX - 1][tempY].count += 1;
		mColliderMap[tempX + 1][tempY].count += 1;
		mColliderMap[tempX][tempY - 1].count += 1;
		mColliderMap[tempX][tempY + 1].count += 1;
		mColliderMap[tempX -1 ][tempY - 1].count += 1;
		mColliderMap[tempX + 1][tempY + 1].count += 1;

	}
}

void GameWorld::SetLevel(const std::uint32_t levelID) {

	componentRegistry.RemoveEntity(mLevelEntity);
	auto level { mLevelManager.LoadLevel(levelID) };
	mLevelEntity = mFactory.CreateEntity(mEntityManager, level);
	mCurrentLevelId = levelID;
}

void GameWorld::CreateBird(std::shared_ptr<sf::Texture> texture, sf::Vector2f position, Entity& player) {

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
		FollowBehaviour{ player }
	);
	componentRegistry.AddComponent(bird,
		Button(
			[bird, this]() {
				auto evolutionState = componentRegistry.GetComponentOfType<EvolutionState>(bird);
				auto entityState = componentRegistry.GetComponentOfType<EntityState>(bird);
				auto entityAnimation = componentRegistry.GetComponentOfType<Animation>(bird);
				auto entityFollow = componentRegistry.GetComponentOfType<FollowBehaviour>(bird);

				if (evolutionState && evolutionState->state == State::UNEVOLVED) {

					entityState->state = State::EVOLVING;
					entityFollow->isFollowActive = true;
					componentRegistry.RemoveComponent<Animation>(bird);
					componentRegistry.AddComponent<Animation>(bird, birdAnimation);
				}

				this->NotifyObservers(bird, EntityEvent::INTERACTION);
			}
		)
	);
}

Entity GameWorld::CreatePlayer(std::shared_ptr<sf::Texture> texture, sf::Vector2f position, float speed) {

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

uint8_t GameWorld::GetColliderCount(uint32_t x, uint32_t y) {

	return mColliderMap[x][y].count;
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


