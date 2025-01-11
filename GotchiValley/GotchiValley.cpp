#include <iostream>
#include <fstream>
#include "GotchiValley.h"
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


using namespace GotchiValley;

	int main()
	{
		auto window = std::make_shared<sf::RenderWindow>(sf::RenderWindow(sf::VideoMode({ 800,600 }), "Gotchi Valley"));
		window->setFramerateLimit(60);

		EntityManager entityManager;
		ComponentManager<Transform> transformManager;
		ComponentManager<Moveable> moveableManager;
		ComponentManager<Controlable> controlableManager;
		ComponentManager<sf::Sprite> spriteManager;
		ComponentManager<sf::Texture> textureManager;
		ComponentManager<Collider> colliderManager;
		ComponentManager<PlayerStats> statsManager;

		GameWorld gameWorld;
		CollisionSystem collisionSystem;
		MovementSystem movementSystem;
		RenderSystem renderSystem;
		PhysicsSystem physicsSystem;
		UISystem uiSystem{ window, gameWorld };


		Entity player = entityManager.CreateEntity();
		const sf::Texture texture = sf::Texture("player.png");
		textureManager.AddComponent(player, texture);
		spriteManager.AddComponent(player, sf::Sprite(texture));
		transformManager.AddComponent(player, Transform({ sf::Vector2f(200,100), sf::Vector2f(0,0), 80.f}));
		colliderManager.AddComponent(player, Collider({ sf::FloatRect( {200,100}, {31,50} ) }));
		moveableManager.AddComponent(player, Moveable());
		controlableManager.AddComponent(player, Controlable());
		statsManager.AddComponent(player, PlayerStats(100));


		Entity object = entityManager.CreateEntity();
		const sf::Texture texture1 = sf::Texture("egg_big.png");
		textureManager.AddComponent(object, texture1);
		spriteManager.AddComponent(object, sf::Sprite(texture1));
		transformManager.AddComponent(object,
			Transform({
				sf::Vector2f(100,50),
				sf::Vector2f(0,0),
				})
				);
		colliderManager.AddComponent(object, Collider({ sf::FloatRect({100,50}, {42,58}) }));


		sf::Clock clock;

		while (window->isOpen()) {

			float dt = clock.restart().asSeconds();

			gameWorld.PollEvents(window);

			movementSystem.Update(transformManager, controlableManager);
			collisionSystem.Update(transformManager, colliderManager, moveableManager);
			physicsSystem.Update(transformManager, spriteManager, colliderManager, dt);
			
			window->clear();
			renderSystem.Update(spriteManager, *window);
			window->display();

		}

		return 0;
	}


