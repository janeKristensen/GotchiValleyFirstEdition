
#include "GameWorld.h"
#include "Animations.h"

using namespace GotchiValley;

void GameWorld::Initialize() {
	
	componentRegistry.RegisterComponentManager<Transform>();
	componentRegistry.RegisterComponentManager<Moveable>();
	componentRegistry.RegisterComponentManager<Controlable>();
	componentRegistry.RegisterComponentManager<Sprite>();
	componentRegistry.RegisterComponentManager<Level>();
	componentRegistry.RegisterComponentManager<Collider>();
	componentRegistry.RegisterComponentManager<PlayerStats>();
	componentRegistry.RegisterComponentManager<Animation>();
	componentRegistry.RegisterComponentManager<Interactable>();

	auto birdTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_sprite_sheet.png")));
	auto playerTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("sprite_sheet.png")));
	auto BigEgg = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_big.png")));

	auto newLevel = Level{ mLevelManager.LoadLevel(0) };
	mCurrentLevel = mFactory.CreateEntity(mEntityManager, newLevel);
	for (std::uint32_t i = 0; i < newLevel.colliders.size(); i++) {

		componentRegistry.AddComponent(mCurrentLevel, newLevel.colliders[i]);
	}

	auto bird1 = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(birdTexture),
		birdAnimation,
		Transform({ sf::Vector2f(100,50), sf::Vector2f(0,0), }),
		Collider({ sf::FloatRect({100,50}, {32,32}) }),
		Interactable()
	);

	auto bird2 = mFactory.CreateEntity
	(
		mEntityManager,
		birdAnimation,
		Sprite(birdTexture),
		Transform({ sf::Vector2f(200,200), sf::Vector2f(0,0) }),
		Collider({ sf::FloatRect({200,200}, {32,32}) }),
		Interactable()
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
}

void GameWorld::Update() {

	// How to implement game logic with entity system?? I want to push an object to change level.
	// How do i reference the objects created in initialization. 
}

void GameWorld::SetLevel(std::uint32_t levelID) {

	componentRegistry.RemoveComponent<Level>(mCurrentLevel);
	componentRegistry.AddComponent<Level>(mCurrentLevel, Level{ mLevelManager.LoadLevel(levelID) });
}


void GameWorld::AddObserver(IWindowObserver* observer){
	
	mObservers.emplace_back(observer);
}

void GameWorld::RemoveObserver(IWindowObserver* observer) {
	
	mObservers.remove(observer);
}

void GameWorld::NotifyObservers(const sf::Event& event, const std::string& message) const {
	
	for (auto observer : mObservers) {
		observer->OnNotify(event, message);
	}
}


