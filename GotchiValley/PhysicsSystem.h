#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"

class PhysicsSystem {
public:
	void RotateEntity(Entity entity, float rotation);
	void MoveEntity(Entity entity, sf::Vector2f transform);

private:

};