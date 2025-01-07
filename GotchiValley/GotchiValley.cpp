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

EntityManager entityManager;

int main()
{
	auto window = std::make_shared<sf::RenderWindow> ( sf::RenderWindow(sf::VideoMode({ 800,600 }), "Gotchi Valley"));
	
	RenderSystem renderSystem;
	GameWorld gameWorld;
	PhysicsSystem physicsSystem{ gameWorld };
	UISystem uiSystem{ window, gameWorld };

	auto player = entityManager.CreateEntity();

	sf::VertexArray playerRect(sf::PrimitiveType::TriangleStrip, 8);
	playerRect[0].position = sf::Vector2f(10.f, 10.f);
	playerRect[1].position = sf::Vector2f(10.f, 50.f);
	playerRect[2].position = sf::Vector2f(50.f, 10.f);
	playerRect[3].position = sf::Vector2f(50.f, 50.f);
	playerRect[4].position = sf::Vector2f(50.f, 50.f);
	playerRect[5].position = sf::Vector2f(10.f, 50.f);
	playerRect[6].position = sf::Vector2f(50.f, 10.f);
	playerRect[7].position = sf::Vector2f(10.f, 10.f);

	playerRect[0].texCoords = sf::Vector2f(0.f, 0.f);
	playerRect[1].texCoords = sf::Vector2f(0.f, 40.f);
	playerRect[2].texCoords = sf::Vector2f(40.f, 0.f);
	playerRect[3].texCoords = sf::Vector2f(40.f, 40.f);
	playerRect[4].texCoords = sf::Vector2f(40.f, 40.f);
	playerRect[5].texCoords = sf::Vector2f(0.f, 40.f);
	playerRect[6].texCoords = sf::Vector2f(40.f, 0.f);
	playerRect[7].texCoords = sf::Vector2f(0.f, 0.f);


	player.AddComponent(sf::Texture());
	player.AddComponent(playerRect);
	player.AddComponent(
		Transform({
			sf::Vector2f(0,0),
			sf::Vector2f(0,0),
			sf::Vector2f(0,0),
			sf::Transform()
		}));
	player.AddComponent(sf::RenderStates());
	player.AddComponent(PlayerStats({50, 100}));
	
	renderSystem.LoadTexture(player, "star.png");

	sf::Clock clock;
	float dt;

	while (window->isOpen()) {

		dt = clock.restart().asSeconds();
		gameWorld.PollEvents(player, window);
		
		physicsSystem.Update(player, dt);

		window->clear();
		renderSystem.Draw(player, *window);	
	}
	
	
	return 0;
}
