#include "PhysicsSystem.h"
#include "Components.h"



void PhysicsSystem::RotateEntity(Entity entity, float rotation) {

	sf::Transform& transform = *entity.GetComponentOfType<sf::Transform>();
	transform.rotate(sf::degrees(rotation));
}

void PhysicsSystem::MoveEntity(Entity entity, sf::Vector2f velocity) 
{
	Transform& transform = *entity.GetComponentOfType<Transform>();
	transform.velocity = velocity;
}

void PhysicsSystem::Update(Entity entity, float dt) {

	Transform& transform = *entity.GetComponentOfType<Transform>();
	auto stats = *entity.GetComponentOfType<PlayerStats>();
	sf::Vector2f movement = transform.velocity * dt * stats.speed;

	transform.transform.translate(movement);

}