#include "PhysicsSystem.h"



void PhysicsSystem::RotateEntity(Entity entity, float rotation) {

	sf::Transform& transform = *entity.GetComponentOfType<sf::Transform>();
	transform.rotate(sf::degrees(rotation));
}

void PhysicsSystem::MoveEntity(Entity entity, sf::Vector2f transform) 
{
	sf::Transform& translation = *entity.GetComponentOfType<sf::Transform>();
	translation = translation.translate(transform);
}