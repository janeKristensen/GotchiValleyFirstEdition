
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
		Collider({ sf::FloatRect({250,150}, {32,32}), sf::RectangleShape{{(float)TILE_SIZE.x , (float)TILE_SIZE.y } } }),
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


void GameWorld::SetLevel(const std::uint32_t levelID) {

	componentRegistry.RemoveEntity(mLevelEntity);
	componentRegistry.AddComponent<Level>(levelID, Level{ mLevelManager.LoadLevel(levelID) });
	mCurrentLevelId = levelID;
}

void GameWorld::CreateBird(std::shared_ptr<sf::Texture> texture, sf::Vector2f position, Entity& player) {

	auto bird = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(texture),
		birdAnimation,
		Transform({ position, {0.f, 0.f}, 30.f }),
		Collider({ sf::FloatRect({position.x , position.y }, { TILE_SIZE.x , TILE_SIZE.y }), sf::RectangleShape{{(float)TILE_SIZE.x, (float)TILE_SIZE.y} } }),
		Interactable(),
		EntityState{ State::INITIAL },
		FollowBehaviour{ player }
	);
	componentRegistry.AddComponent(bird,
		Button(
			[bird, this]() {
				auto entityState = componentRegistry.GetComponentOfType<EntityState>(bird);
				auto entityAnimation = componentRegistry.GetComponentOfType<Animation>(bird);
				if (entityState && entityState->state == State::INITIAL) {

					entityState->state = State::EVOLVING;
					entityAnimation->frames[AnimationName::COLLIDING] = birdAnimation.frames[AnimationName::IDLE];
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
		Collider({ sf::FloatRect({position.x , position.y  }, { TILE_SIZE.x , TILE_SIZE.y  }), sf::RectangleShape{{(float)TILE_SIZE.x, (float)TILE_SIZE.y} } }),
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


