#include "PhysicsSystem.h"
#include "Components.h"

PhysicsSystem::PhysicsSystem(ISubject& subject) : mSubject(subject) 
{
	this->mSubject.AddObserver(this);
}


void PhysicsSystem::RemoveFromSubject() {
	mSubject.RemoveObserver(this);
}


void PhysicsSystem::OnNotify(Entity& entity, const sf::Event& event) {

	if (event.is<sf::Event::KeyPressed>()) {

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
	else if (event.is<sf::Event::KeyReleased>()) {
		StopEntityMovement(entity);
	}
}


void PhysicsSystem::Update(Entity& entity, float dt) {

	Transform& transform = *entity.GetComponentOfType<Transform>();
	auto stats = *entity.GetComponentOfType<PlayerStats>();
	sf::Vector2f movement = transform.velocity * dt * stats.speed;

	transform.transform.translate(movement);
}


void PhysicsSystem::RotateEntity(Entity& entity, float rotation) {

	sf::Transform& transform = *entity.GetComponentOfType<sf::Transform>();
	transform.rotate(sf::degrees(rotation));
}


void PhysicsSystem::MoveEntity(Entity& entity, DIRECTION direction) 
{
	Transform& transform = *entity.GetComponentOfType<Transform>();

	switch (direction) {
	case UP:
		transform.velocity.y = -1.f;
		break;
	case DOWN:
		transform.velocity.y = 1.f;
		break;
	case LEFT:
		transform.velocity.x = -1.f;
		break;
	case RIGHT:
		transform.velocity.x = 1.f;
		break;
	}
}


void PhysicsSystem::StopEntityMovement(Entity& entity) {
	Transform& transform = *entity.GetComponentOfType<Transform>();
	transform.velocity = sf::Vector2f(0.f, 0.f);
}





