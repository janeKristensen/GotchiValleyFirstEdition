#include "PhysicsSystem.h"



void PhysicsSystem::RotateEntity(Entity entity, float rotation) {

	sf::Transform& transform = *entity.GetComponentOfType<sf::Transform>();
	transform.rotate(sf::degrees(rotation));
}

void PhysicsSystem::MoveEntity(Entity entity, sf::Vector2f velocity) 
{
	sf::Transform& translation = *entity.GetComponentOfType<sf::Transform>();
	translation = translation.translate(velocity);
}

void PhysicsSystem::Update(Entity entity, float dt) {

	sf::Transform& transform = *entity.GetComponentOfType<sf::Transform>();

}