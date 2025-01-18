
#include "GotchiValley.h"



using namespace GotchiValley;

	int main()
	{
		auto window = std::make_shared<sf::RenderWindow>(sf::RenderWindow(sf::VideoMode({ 800,600 }), "Gotchi Valley"));
		window->setFramerateLimit(60);

		
		GameWorld gameWorld;
		CollisionSystem collisionSystem;
		MovementSystem movementSystem;
		AnimationSystem animationSystem;
		RenderSystem renderSystem;
		PhysicsSystem physicsSystem;
		UISystem uiSystem{ window, gameWorld };

		componentRegistry.RegisterComponentManager<Transform>();
		componentRegistry.RegisterComponentManager<Moveable>();
		componentRegistry.RegisterComponentManager<Controlable>();
		componentRegistry.RegisterComponentManager<Sprite>();
		componentRegistry.RegisterComponentManager<Collider>();
		componentRegistry.RegisterComponentManager<PlayerStats>();
		componentRegistry.RegisterComponentManager<Animation>();

		gameWorld.Initialize();

		//Entity player = entityManager.CreateEntity();
		//auto texture = std::make_shared<sf::Texture>(std::move(sf::Texture("sprite_sheet.png")));
		//auto animation1 = AnimationData(8, { sf::IntRect({ 0,32 }, { 32,32 }),
		//	sf::IntRect({ 32,0 }, { 32,32 }),
		//	sf::IntRect({ 64,0 }, { 32,32 }),
		//	sf::IntRect({ 96,0 }, { 32,32 }),
		//	sf::IntRect({ 128,0 }, { 32,32 }),
		//	sf::IntRect({ 160,0 }, { 32,32 }),
		//	sf::IntRect({ 192,0 }, { 32,32 }),
		//	sf::IntRect({ 224,0 }, { 32,32 }),
		//	sf::IntRect({ 256,0 }, { 32,32 }),
		//	sf::IntRect({ 288,0 }, { 32,32 }),
		//	sf::IntRect({ 320,0 }, { 32,32 }),
		//	sf::IntRect({ 352,0 }, { 32,32 }),
		//	sf::IntRect({ 384,0 }, { 32,32 }),
		//	}, 10.f);

		//auto animation2 = AnimationData(8, { sf::IntRect({ 0,32 }, { 32,32 }),
		//	sf::IntRect({ 32,32 }, { 32,32 }),
		//	sf::IntRect({ 64,32 }, { 32,32 }),
		//	sf::IntRect({ 96,32 }, { 32,32 }),
		//	sf::IntRect({ 128,32 }, { 32,32 }),
		//	sf::IntRect({ 160,32 }, { 32,32 }),
		//	sf::IntRect({ 192,32 }, { 32,32 }),
		//	sf::IntRect({ 224,32 }, { 32,32 }), });

		//componentRegistry.AddComponent(player, Animation({animation1, animation2}));
		//componentRegistry.AddComponent(player, Sprite(texture));
		//componentRegistry.AddComponent(player, Transform({ sf::Vector2f(200,100), sf::Vector2f(0,0), 80.f }));
		//componentRegistry.AddComponent(player, Collider({ sf::FloatRect({200,100}, {31,50}) }));
		//componentRegistry.AddComponent(player, Moveable());
		//componentRegistry.AddComponent(player, Controlable());
		//componentRegistry.AddComponent(player, PlayerStats(100)); 


		//Entity object = entityManager.CreateEntity();
		//auto texture1 = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_big.png")));
		//componentRegistry.AddComponent(object, Sprite(texture1));
		//componentRegistry.AddComponent(object,
		//	Transform({
		//		sf::Vector2f(100,50),
		//		sf::Vector2f(0,0),
		//		})
		//		);
		//componentRegistry.AddComponent(object, Collider({ sf::FloatRect({100,50}, {42,58}) }));

		sf::Clock clock;

		while (window->isOpen()) {

			float dt = clock.restart().asSeconds();

			gameWorld.PollEvents(window);

			movementSystem.Update();
			collisionSystem.Update();
			physicsSystem.Update(dt);
			animationSystem.Update(dt);
			
			window->clear();
			renderSystem.Update(*window);
			window->display();

		}

		return 0;
	}


