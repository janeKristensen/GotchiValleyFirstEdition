
#include "GotchiValley.h"

using namespace GotchiValley;

	int main()
	{
		auto window = std::make_shared<sf::RenderWindow>(sf::RenderWindow(sf::VideoMode({ SCREEN_SIZE.x, SCREEN_SIZE.y }), "Gotchi Valley"));
		window->setFramerateLimit(60);
		
		LevelManager levelManager = LevelManager(std::make_shared<sf::Texture>(std::move<sf::Texture>(sf::Texture{ "bg_sprite_small.png" })));
		GameWorld gameWorld{ levelManager };
		
		UISystem uiSystem;
		RenderSystem renderSystem(gameWorld);
		CollisionSystem collisionSystem(gameWorld);
		MovementSystem movementSystem(gameWorld);
		PhysicsSystem physicsSystem{gameWorld, &collisionSystem, &movementSystem };
		AnimationSystem animationSystem{gameWorld, &collisionSystem, &movementSystem, &uiSystem, &gameWorld };
		

		sf::Clock clock;
		gameWorld.initialize();

		while (window->isOpen()) {

			float dt = clock.restart().asSeconds();

			uiSystem.update(window);

			movementSystem.update(dt);
			collisionSystem.update();
			physicsSystem.update(dt);
			animationSystem.update(dt);

			window->clear();
			renderSystem.update(*window);
			window->display();

		}

		return 0;
	}


