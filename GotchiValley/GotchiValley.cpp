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

const std::size_t MAX_ENTITIES{ 1000 };

EntityManager entityManager;

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Gotchi Valley");
	PhysicsSystem physicsSystem;
	RenderSystem renderSystem;

	auto player = entityManager.CreateEntity();

	sf::VertexArray rect(sf::PrimitiveType::TriangleStrip, 8);
	rect[0].position = sf::Vector2f(10.f, 10.f);
	rect[1].position = sf::Vector2f(10.f, 50.f);
	rect[2].position = sf::Vector2f(50.f, 10.f);
	rect[3].position = sf::Vector2f(50.f, 50.f);
	rect[4].position = sf::Vector2f(50.f, 50.f);
	rect[5].position = sf::Vector2f(10.f, 50.f);
	rect[6].position = sf::Vector2f(50.f, 10.f);
	rect[7].position = sf::Vector2f(10.f, 10.f);

	rect[0].texCoords = sf::Vector2f(0.f, 0.f);
	rect[1].texCoords = sf::Vector2f(0.f, 40.f);
	rect[2].texCoords = sf::Vector2f(40.f, 0.f);
	rect[3].texCoords = sf::Vector2f(40.f, 40.f);
	rect[4].texCoords = sf::Vector2f(40.f, 40.f);
	rect[5].texCoords = sf::Vector2f(0.f, 40.f);
	rect[6].texCoords = sf::Vector2f(40.f, 0.f);
	rect[7].texCoords = sf::Vector2f(0.f, 0.f);


	player.AddComponent(sf::Texture());
	player.AddComponent(rect);
	player.AddComponent(sf::Transform());
	player.AddComponent(sf::RenderStates());
	player.AddComponent(PlayerStats({10, 100}));
	
	renderSystem.LoadTexture(player, "star.png");

	sf::Clock clock;
	float dt;

	while (window.isOpen()) {

		dt = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent()) {

			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

			if (event->is<sf::Event::KeyPressed>()) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
					window.close();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
					auto stats = *player.GetComponentOfType<PlayerStats>();
					physicsSystem.MoveEntity(player, sf::Vector2f(0, stats.speed));
				}
			}
		}
		physicsSystem.Update(player, dt);

		window.clear();
		renderSystem.Draw(player, window);	
	}
	
	
	return 0;
}
