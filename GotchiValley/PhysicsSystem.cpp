#include "PhysicsSystem.h"
#include "Components.h"
#include <iostream>

PhysicsSystem::PhysicsSystem(ISubject& subject) : mSubject(subject) 
{
	this->mSubject.AddObserver(this);
}


void PhysicsSystem::RemoveFromSubject() {
	mSubject.RemoveObserver(this);
}


void PhysicsSystem::OnNotify(EntityManager& manager, const sf::Event& event) {

	if (event.is<sf::Event::KeyPressed>()) {
		for (uint32_t i = 0; i < MAX_ENTITIES; i++) {

			auto controlable = manager.HasComponent<Controlable>(i);
			if (!controlable) continue;
			auto entity = manager.GetEntity(i);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
				MoveEntity(entity, DIRECTION::UP);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
				MoveEntity(entity, DIRECTION::DOWN);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
				MoveEntity(entity, DIRECTION::RIGHT);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
				MoveEntity(entity, DIRECTION::LEFT);
			}

		}
	}	
}


void PhysicsSystem::Update(EntityManager& manager, float dt) {

	for (uint32_t i = 0; i < MAX_ENTITIES; i++) {

		auto transform = manager.GetComponent<Transform>(i);
		auto sprite = manager.GetComponent<sf::Sprite>(i);
		auto stats = manager.GetComponent<PlayerStats>(i);
		float speed = stats ? stats->speed : .0f;

		if (!transform) continue;
		transform->position += transform->velocity * dt * speed;

		if (sprite) {
			sprite->setPosition(transform->position);
		}
		
		std::cout << "x: " + std::to_string(transform->velocity.x) + " y:" + std::to_string(transform->velocity.y) << std::endl;

		transform->velocity = .99f * transform->velocity;

	}
}


void PhysicsSystem::RotateEntity(std::shared_ptr<Entity> entity, float rotation) {

	sf::Transform& transform = *entity->GetComponentOfType<sf::Transform>();
	transform.rotate(sf::degrees(rotation));
}


void PhysicsSystem::MoveEntity(std::shared_ptr<Entity> entity, DIRECTION direction) 
{
	Transform& transform = *entity->GetComponentOfType<Transform>();
	float acceleration = 1.f;

	if(direction == UP) transform.velocity.y = -acceleration;
	if(direction == DOWN) transform.velocity.y = acceleration;
	if (direction == LEFT) transform.velocity.x = -acceleration;
	if (direction == RIGHT) transform.velocity.x = acceleration;
	
}








