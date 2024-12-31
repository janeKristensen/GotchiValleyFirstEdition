// GotchiValley.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <fstream>
#include "GotchiValley.h"
#include "EntityManager.h"
#include "SFML/Graphics.hpp"
#include "PhysicsSystem.h"
#include "RenderSystem.h"

const std::size_t MAX_ENTITIES{ 1000 };

EntityManager entityManager;

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Gotchi Valley");
	PhysicsSystem physicsSystem;
	RenderSystem renderSystem;

	auto player = entityManager.CreateEntity();
	sf::Texture texture;
	if (!texture.loadFromFile(std::filesystem::absolute("star.png").string()))
	{
		throw std::runtime_error("Could not load image.png");
	}

	player.AddComponent(sf::Sprite(texture));
	player.AddComponent(sf::Transform());
	player.AddComponent(sf::Color(255, 255, 255, 1));
	physicsSystem.MoveEntity(player, sf::Vector2f(100, 200));
	

	while (window.isOpen()) {

		while (const std::optional event = window.pollEvent()) {

			if (event->is<sf::Event::Closed>()) { 
				window.close(); 
			}

			if (event->is<sf::Event::KeyPressed>()) {
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
					window.close();
				}
			}
		}

		renderSystem.Draw(player, window);
		
	}
	
	
	return 0;
}
