// GotchiValley.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <fstream>
#include "GotchiValley.h"
#include "EntityManager.h"
#include "SFML/Graphics.hpp"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "Components.h"
#include "UISystem.h"
#include "GameWorld.h"

const std::size_t MAX_ENTITIES{ 1000 };


int main()
{
	auto window = std::make_shared<sf::RenderWindow> ( sf::RenderWindow(sf::VideoMode({ 800,600 }), "Gotchi Valley"));
	window->setFramerateLimit(60);

	EntityManager entityManager;
	RenderSystem renderSystem;
	GameWorld gameWorld;
	PhysicsSystem physicsSystem{ gameWorld };
	UISystem uiSystem{ window, gameWorld };
	

	auto player = entityManager.CreateEntity();
	const sf::Texture texture = sf::Texture("star.png");
	entityManager.AddComponent(*player, texture);
	entityManager.AddComponent(*player, sf::Sprite(texture));
	entityManager.AddComponent(*player,
		Transform({
			sf::Vector2f(0,0),
			sf::Vector2f(0,0),
			sf::Vector2f(0,0),
		})
	);
	entityManager.AddComponent(*player, Collider({ sf::FloatRect({0,0}, {40,40}) }));
	entityManager.AddComponent(*player, Moveable());
	entityManager.AddComponent(*player, Controlable());
	entityManager.AddComponent(*player, PlayerStats({100, 100}));
	
	auto object = entityManager.CreateEntity();
	const sf::Texture texture1 = sf::Texture("egg_big.png");
	entityManager.AddComponent(*object, texture1);
	entityManager.AddComponent(*object, sf::Sprite(texture1));
	entityManager.AddComponent(*object,
		Transform({
			sf::Vector2f(100,50),
			sf::Vector2f(0,0),
			sf::Vector2f(0,0),
		})
	);
	entityManager.AddComponent(*object, Collider({ sf::FloatRect({0,0}, {42,58}) }));
	

	sf::Clock clock;
	
	while (window->isOpen()) {

		float dt = clock.restart().asSeconds();

		gameWorld.PollEvents(entityManager, window);
		physicsSystem.Update(entityManager, dt);
		renderSystem.Draw(entityManager, *window);	
	}
	
	return 0;
}
