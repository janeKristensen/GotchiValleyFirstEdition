
#include "GameWorld.h"


using namespace GotchiValley;

void GameWorld::Initialize() {
	
	EntityManager entityManager;

	auto player = entityManager.CreateEntity();
	auto texture = std::make_shared<sf::Texture>(std::move(sf::Texture("sprite_sheet.png")));
	componentRegistry.AddComponent(player, Sprite(texture));
	auto animation1 = AnimationData(8, 
		{ 
			sf::IntRect({ 0,32 }, { 32,32 }),
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
		}, 5.f);

	auto animation2 = AnimationData(8, 
		{
			sf::IntRect({ 0,32 }, { 32,32 }),
			sf::IntRect({ 32,32 }, { 32,32 }),
			sf::IntRect({ 64,32 }, { 32,32 }),
			sf::IntRect({ 96,32 }, { 32,32 }),
			sf::IntRect({ 128,32 }, { 32,32 }),
			sf::IntRect({ 160,32 }, { 32,32 }),
			sf::IntRect({ 192,32 }, { 32,32 }),
			sf::IntRect({ 224,32 }, { 32,32 }), 
		}, 16.f);

	componentRegistry.AddComponent(player, Animation({ animation1, animation2 }));
	componentRegistry.AddComponent(player, Transform({ sf::Vector2f(200,100), sf::Vector2f(0,0), 80.f }));
	componentRegistry.AddComponent(player, Collider({ sf::FloatRect({200,100}, {31,50}) }));
	componentRegistry.AddComponent(player, Moveable());
	componentRegistry.AddComponent(player, Controlable());
	componentRegistry.AddComponent(player, PlayerStats(100));


	auto object = entityManager.CreateEntity();
	auto texture1 = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_big.png")));
	componentRegistry.AddComponent(object, Sprite(texture1));
	componentRegistry.AddComponent(object,
		Transform({
			sf::Vector2f(100,50),
			sf::Vector2f(0,0),
			})
			);
	componentRegistry.AddComponent(object, Collider({ sf::FloatRect({100,50}, {42,58}) }));
}

void GameWorld::AddObserver(IObserver* observer){
	
	mObservers.emplace_back(observer);
}

void GameWorld::RemoveObserver(IObserver* observer) {
	
	mObservers.remove(observer);
}

void GameWorld::NotifyObservers(const sf::Event& event, const std::string& message) {
	
	for (auto observer : mObservers) {
		observer->OnNotify(event, message);
	}
}


void GameWorld::PollEvents(std::shared_ptr<sf::RenderWindow> window) {

	while (const std::optional event = window->pollEvent()) {

		NotifyObservers(event.value(), "");
	}
}

