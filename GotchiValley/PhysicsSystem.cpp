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

	if (message == "collision") {

	}
	
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

		transform->velocity = .99f * transform->velocity;	
	}
}


void PhysicsSystem::RotateEntity(std::shared_ptr<Entity> entity, float rotation) {

	sf::Transform& transform = *entity->GetComponentOfType<sf::Transform>();
	transform.rotate(sf::degrees(rotation));
}


void PhysicsSystem::ResolveCollisions(EntityManager& manager) {

	std::vector<uint32_t> colliderEntities;

	for (uint32_t i = 0; i < MAX_ENTITIES; i++) {

		auto component = manager.GetComponent<Collider>(i);
		if (component) {

			colliderEntities.emplace_back(i);
		}
	}

	for (uint32_t i = 0; i < colliderEntities.size() - 1; i++) {

		auto collider1 = manager.GetComponent<Collider>(colliderEntities[i]);

		for (uint32_t j = 1; j < colliderEntities.size(); j++) {

			auto collider2 = manager.GetComponent<Collider>(colliderEntities[j]);
			if (collider1->boundingBox.findIntersection(collider2->boundingBox))
			{
				auto transform = manager.GetComponent<Transform>(i);
				transform->position -= transform->velocity;
			}
		}
	}
}










