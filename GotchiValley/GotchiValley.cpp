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
		}));
	entityManager.AddComponent(*player, Controlable());
	entityManager.AddComponent(*player, PlayerStats({100, 100}));
	
	

	sf::Clock clock;
	float dt;

	while (window->isOpen()) {

		dt = clock.restart().asSeconds();
		gameWorld.PollEvents(entityManager, window);
		
		physicsSystem.Update(entityManager, dt);

		window->clear();
		renderSystem.Draw(entityManager, *window);	
	}
	
	
	return 0;
}
