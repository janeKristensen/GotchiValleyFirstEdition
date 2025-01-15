
#include "GotchiValley.h"
#include "ComponentRegistry.h"
#include "SharedObjects.h"
#include "EntityManager.h"
#include "SFML/Graphics.hpp"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "Components.h"
#include "UISystem.h"
#include "GameWorld.h"
#include "ComponentManager.h"
#include <iostream>
#include <fstream>




using namespace GotchiValley;

	int main()
	{
		auto window = std::make_shared<sf::RenderWindow>(sf::RenderWindow(sf::VideoMode({ 800,600 }), "Gotchi Valley"));
		window->setFramerateLimit(60);

		EntityManager entityManager;
		GameWorld gameWorld;
		CollisionSystem collisionSystem;
		MovementSystem movementSystem;
		RenderSystem renderSystem;
		PhysicsSystem physicsSystem;
		UISystem uiSystem{ window, gameWorld };

		componentRegistry.RegisterComponentManager<Transform>();
		componentRegistry.RegisterComponentManager<Moveable>();
		componentRegistry.RegisterComponentManager<Controlable>();
		componentRegistry.RegisterComponentManager<sf::Sprite>();
		componentRegistry.RegisterComponentManager<sf::Texture>();
		componentRegistry.RegisterComponentManager<Collider>();
		componentRegistry.RegisterComponentManager<PlayerStats>();


		Entity player = entityManager.CreateEntity();
		const sf::Texture texture = sf::Texture("player.png");
		componentRegistry.AddComponent(player, texture);
		componentRegistry.AddComponent(player, sf::Sprite(texture));
		componentRegistry.AddComponent(player, Transform({ sf::Vector2f(200,100), sf::Vector2f(0,0), 80.f }));
		componentRegistry.AddComponent(player, Collider({ sf::FloatRect({200,100}, {31,50}) }));
		componentRegistry.AddComponent(player, Moveable());
		componentRegistry.AddComponent(player, Controlable());
		componentRegistry.AddComponent(player, PlayerStats(100)); 


		Entity object = entityManager.CreateEntity();
		const sf::Texture texture1 = sf::Texture("egg_big.png");
		componentRegistry.AddComponent(object, texture1);
		componentRegistry.AddComponent(object, sf::Sprite(texture1));
		componentRegistry.AddComponent(object,
			Transform({
				sf::Vector2f(100,50),
				sf::Vector2f(0,0),
				})
				);
		componentRegistry.AddComponent(object, Collider({ sf::FloatRect({100,50}, {42,58}) }));

		sf::Clock clock;

		while (window->isOpen()) {

			float dt = clock.restart().asSeconds();

			gameWorld.PollEvents(window);

			movementSystem.Update();
			collisionSystem.Update();
			physicsSystem.Update(dt);
			
			window->clear();
			renderSystem.Update(*window);
			window->display();

		}

		return 0;
	}


