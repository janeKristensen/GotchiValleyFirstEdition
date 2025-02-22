
#include "GameWorld.h"
#include "Animations.h"

using namespace GotchiValley;

void GameWorld::Initialize() {
	
	componentRegistry.RegisterComponentManager<Transform>();
	componentRegistry.RegisterComponentManager<Moveable>();
	componentRegistry.RegisterComponentManager<Controlable>();
	componentRegistry.RegisterComponentManager<Sprite>();
	componentRegistry.RegisterComponentManager<Collider>();
	componentRegistry.RegisterComponentManager<PlayerStats>();
	componentRegistry.RegisterComponentManager<Animation>();
	componentRegistry.RegisterComponentManager<Interactable>();

	EntityManager entityManager;
	Factory factory;

	auto birdTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_sprite_sheet.png")));
	auto playerTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("sprite_sheet.png")));

	auto bird1 = factory.CreateEntity
	(
		entityManager,
		Sprite(birdTexture),
		birdAnimation,
		Transform({ sf::Vector2f(100,50), sf::Vector2f(0,0), }),
		Collider({ sf::FloatRect({100,50}, {32,32}) }),
		Interactable()
	);

	auto bird2 = factory.CreateEntity
	(
		entityManager,
		birdAnimation,
		Sprite(birdTexture),
		Transform({ sf::Vector2f(200,200), sf::Vector2f(0,0) }),
		Collider({ sf::FloatRect({200,200}, {32,32}) }),
		Interactable()
	);

	auto player = factory.CreateEntity
	(
		entityManager,
		Sprite(playerTexture),
		playerAnimation,
		Transform({ sf::Vector2f(200,100), sf::Vector2f(0,0), 80.f }),
		Collider({ sf::FloatRect({200,100}, {32,32}) }),
		Moveable(),
		Controlable(),
		PlayerStats(100)
	);

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


