
#include "GameWorld.h"


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

	auto object = entityManager.CreateEntity();
	auto texture1 = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_sprite_sheet.png")));
	componentRegistry.AddComponent(object, Sprite(texture1));
	auto animEgg = AnimationData(1,
		{
			sf::IntRect({ 0,0 }, { 32,32 }),
		});
	auto animBird = AnimationData(4,
		{
			sf::IntRect({ 0,32 }, { 32,32 }),
			sf::IntRect({ 32,32 }, { 32,32 }),
			sf::IntRect({ 64,32 }, { 32,32 }),
			sf::IntRect({ 96,32 }, { 32,32 }),

		}, 2.f);
	auto animCollision = AnimationData( 4,
		{
			sf::IntRect({ 0,160 }, { 32,32 }),
			sf::IntRect({ 32,160 }, { 32,32 }),
			sf::IntRect({ 64,160 }, { 32,32 }),
			sf::IntRect({ 96,160 }, { 32,32 }),

		}, 2.f);
	componentRegistry.AddComponent(object, Animation({ {AnimationName::INITIAL, animEgg}, {AnimationName::IDLE, animBird}, {AnimationName::COLLIDING, animCollision}, {AnimationName::INTERACTING, animBird} }, 0, 0, 0, AnimationName::INITIAL));
	componentRegistry.AddComponent(object,
		Transform(
			{
				sf::Vector2f(100,50),
				sf::Vector2f(0,0),
			}
		));
	componentRegistry.AddComponent(object, Collider({ sf::FloatRect({100,50}, {32,32}) }));
	componentRegistry.AddComponent(object, Interactable());


	auto player = entityManager.CreateEntity();
	auto texture = std::make_shared<sf::Texture>(std::move(sf::Texture("sprite_sheet.png")));
	componentRegistry.AddComponent(player, Sprite(texture));
	auto animStanding = AnimationData( 13,
		{ 
			sf::IntRect({ 0,0 }, { 32,32 }),
			sf::IntRect({ 32,0 }, { 32,32 }),
			sf::IntRect({ 64,0 }, { 32,32 }),
			sf::IntRect({ 96,0 }, { 32,32 }),
			sf::IntRect({ 128,0 }, { 32,32 }),
			sf::IntRect({ 160,0 }, { 32,32 }),
			sf::IntRect({ 192,0 }, { 32,32 }),
			sf::IntRect({ 224,0 }, { 32,32 }),
			sf::IntRect({ 256,0 }, { 32,32 }),
			sf::IntRect({ 288,0 }, { 32,32 }),
			sf::IntRect({ 320,0 }, { 32,32 }),
			sf::IntRect({ 352,0 }, { 32,32 }),
			sf::IntRect({ 384,0 }, { 32,32 }),
		}, 10.f);

	auto animRunning = AnimationData( 8,
		{
			sf::IntRect({ 0,0 }, { 32,32 }),
			sf::IntRect({ 32,32 }, { 32,32 }),
			sf::IntRect({ 64,32 }, { 32,32 }),
			sf::IntRect({ 96,32 }, { 32,32 }),
			sf::IntRect({ 128,32 }, { 32,32 }),
			sf::IntRect({ 160,32 }, { 32,32 }),
			sf::IntRect({ 192,32 }, { 32,32 }),
			sf::IntRect({ 224,32 }, { 32,32 }), 
		}, 16.f);

	auto animColliding = AnimationData( 4,
		{
			sf::IntRect({ 0,196}, { 32,32 }),
			sf::IntRect({ 32,196 }, { 32,32 }),
			sf::IntRect({ 64,196 }, { 32,32 }),
			sf::IntRect({ 96,196 }, { 32,32 }),
		}, 24.f);

	componentRegistry.AddComponent(player, Animation({ {AnimationName::IDLE,animStanding}, {AnimationName::RUNNING, animRunning}, {AnimationName::COLLIDING, animColliding} }, 0, 0, 0, AnimationName::IDLE));
	componentRegistry.AddComponent(player, Transform({ sf::Vector2f(200,100), sf::Vector2f(0,0), 80.f }));
	componentRegistry.AddComponent(player, Collider({ sf::FloatRect({200,100}, {32,32}) }));
	componentRegistry.AddComponent(player, Moveable());
	componentRegistry.AddComponent(player, Controlable());
	componentRegistry.AddComponent(player, PlayerStats(100));


	
}

void GameWorld::AddObserver(IWindowObserver* observer){
	
	mObservers.emplace_back(observer);
}

void GameWorld::RemoveObserver(IWindowObserver* observer) {
	
	mObservers.remove(observer);
}

void GameWorld::NotifyObservers(const sf::Event& event, const std::string& message) {
	
	for (auto observer : mObservers) {
		observer->OnNotify(event, message);
	}
}


