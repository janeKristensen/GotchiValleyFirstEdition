#include "PhysicsSystem.h"
#include "Components.h"
#include <iostream>

extern const size_t MAX_ENTITIES;

PhysicsSystem::PhysicsSystem(ISubject& subject) : mSubject(subject) 
{
	this->mSubject.AddObserver(this);
}


void PhysicsSystem::RemoveFromSubject() {
	mSubject.RemoveObserver(this);
}


void PhysicsSystem::OnNotify(EntityManager& manager, const sf::Event& event, std::string message) {

	
}


void PhysicsSystem::Update(EntityManager& manager, float dt) {

	for (uint32_t i = 0; i < MAX_ENTITIES; i++) {

		auto transform = manager.GetComponent<Transform>(i);
		auto sprite = manager.GetComponent<sf::Sprite>(i);
		auto stats = manager.GetComponent<PlayerStats>(i);
		float speed = stats ? stats->speed : .0f;

		if (!transform) continue;
		
		auto controlable = manager.HasComponent<Controlable>(i);
		if (controlable) {

			float acceleration = 1.f;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
				transform->velocity.y = -acceleration;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
				transform->velocity.y = acceleration;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
				transform->velocity.x = acceleration;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
				transform->velocity.x = -acceleration;
			}
		}
		
		this->ResolveCollisions(manager);

		if (stats) {
			transform->position += transform->velocity * dt * speed;
		}
		else {
			transform->position += transform->velocity * dt;
		}

		if (sprite) {
			sprite->setPosition(transform->position);
			auto collider = manager.GetComponent<Collider>(i);
			collider->boundingBox.position = transform->position;
		}

		transform->velocity = .95f * transform->velocity;	
	}
}


void PhysicsSystem::RotateEntity(std::shared_ptr<Entity> entity, float rotation) {

	sf::Transform& transform = *entity->GetComponentOfType<sf::Transform>();
	transform.rotate(sf::degrees(rotation));
}


void PhysicsSystem::ResolveCollisions(EntityManager& manager) {

	for (uint32_t i = 0; i < MAX_ENTITIES - 1; i++) {

		auto collider1 = manager.GetComponent<Collider>(i);
		if (!collider1) continue;
		
		for (uint32_t j = 1; j < MAX_ENTITIES; j++) {

			auto collider2 = manager.GetComponent<Collider>(j);
			if (!collider2) continue;

			if (collider1->boundingBox.findIntersection(collider2->boundingBox))
			{
				auto hasComponent = manager.GetComponent<Moveable>(i);
				if (hasComponent) {

					auto transform = manager.GetComponent<Transform>(i);
					transform->position -= transform->velocity;
				}
				
			}
		}
	}
}










