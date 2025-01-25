
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


