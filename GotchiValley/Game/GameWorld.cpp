
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

	auto birdTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_sprite_sheet.png")));
	auto playerTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("sprite_sheet.png")));
	auto BigEgg = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_big.png")));

	auto newLevel = Level{ mLevelManager.LoadLevel(1) };
	mCurrentLevelId = newLevel.levelId;
	mCurrentLevel = mFactory.CreateEntity(mEntityManager, newLevel);

	auto bird1 = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(birdTexture),
		birdAnimation,
		Transform({ sf::Vector2f(100,50), sf::Vector2f(0,0), }),
		Collider({ sf::FloatRect({100,50}, {32,32}) }),
		Interactable(),
		EntityState{ State::INITIAL }
	);
	componentRegistry.AddComponent(bird1, 
		Button(
			[bird1, this]() {
				auto entityState = componentRegistry.GetComponentOfType<EntityState>(bird1);
				auto entityAnimation = componentRegistry.GetComponentOfType<Animation>(bird1);
				if (entityState->state == State::EVOLVING) {

					entityAnimation->frames[AnimationName::COLLIDING] = birdAnimation.frames[AnimationName::IDLE];
				}

				this->NotifyObservers(bird1, EntityEvent::INTERACTION);
			}
		)
	);

	auto bird2 = mFactory.CreateEntity
	(
		mEntityManager,
		birdAnimation,
		Sprite(birdTexture),
		Transform({ sf::Vector2f(200,200), sf::Vector2f(0,0) }),
		Collider({ sf::FloatRect({200,200}, {32,32}) }),
		Interactable(),
		EntityState{ State::INITIAL }
	);
	componentRegistry.AddComponent(bird2,
		Button(
			[bird2, this]() {
	
				auto entityState = componentRegistry.GetComponentOfType<EntityState>(bird2);
				auto entityAnimation = componentRegistry.GetComponentOfType<Animation>(bird2);
				if (entityState->state == State::EVOLVING) {

					entityAnimation->frames[AnimationName::COLLIDING] = birdAnimation.frames[AnimationName::IDLE];
				}

				this->NotifyObservers(bird2, EntityEvent::INTERACTION);
			}
		)
	);

	auto player = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(playerTexture),
		playerAnimation,
		Transform({ sf::Vector2f(200,100), sf::Vector2f(0,0), 80.f }),
		Collider({ sf::FloatRect({200,100}, {32,32}) }),
		Moveable(),
		Controlable(),
		PlayerStats(100)
	);

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


void GameWorld::SetLevel(const std::uint32_t levelID) {

	componentRegistry.RemoveComponent<Level>(mCurrentLevel);
	componentRegistry.AddComponent<Level>(mCurrentLevelId, Level{ mLevelManager.LoadLevel(levelID) });
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


