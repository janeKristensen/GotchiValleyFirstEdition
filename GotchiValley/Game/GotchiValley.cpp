
#include "GotchiValley.h"

using namespace GotchiValley;

	int main()
	{
		auto window = std::make_shared<sf::RenderWindow>(sf::RenderWindow(sf::VideoMode({ SCREEN_SIZE.x, SCREEN_SIZE.y }), "Gotchi Valley"));
		window->setFramerateLimit(60);

		
		UISystem uiSystem;
		RenderSystem renderSystem;
		CollisionSystem collisionSystem;
		MovementSystem movementSystem;
		GameWorld gameWorld;

		PhysicsSystem physicsSystem{ &collisionSystem, &movementSystem };
		AnimationSystem animationSystem{ &collisionSystem, &movementSystem, &gameWorld };
		

		gameWorld.Initialize();


		sf::Clock clock;

		while (window->isOpen()) {

			float dt = clock.restart().asSeconds();

			uiSystem.PollEvents(window);

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


