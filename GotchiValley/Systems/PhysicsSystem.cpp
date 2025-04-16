
#include "PhysicsSystem.h"

using namespace GotchiValley;


void PhysicsSystem::Update(float& dt) {

	auto transformArray = componentRegistry.GetComponentArray<Transform>();

	for (auto i = transformArray.begin(); i != transformArray.end(); i++) {

		auto transform = i->second;

		transform->position += transform->velocity * dt * transform->speed;
	
		auto spriteComponent = componentRegistry.GetComponentOfType<Sprite>(i->first);
		if (!spriteComponent) continue;
		spriteComponent->sprite.setPosition(transform->position);

		auto collider = componentRegistry.GetComponentOfType<Collider>(i->first);
		if (!collider) continue;
		collider->boundingBox.position = transform->position;

		transform->velocity = .95f * transform->velocity;	
	}
}


void PhysicsSystem::SetPosition(Entity& entity, sf::Vector2f& position) {

	auto transform = componentRegistry.GetComponentOfType<Transform>(entity);
	if (!transform) return;
	transform->position = position;

	auto spriteComponent = componentRegistry.GetComponentOfType<Sprite>(entity);
	if (!spriteComponent) return;
	spriteComponent->sprite.setPosition(transform->position);
	
}


void PhysicsSystem::OnNotify(const Entity& entity, const EntityEvent& eventMessage) {

	auto transform = componentRegistry.GetComponentOfType<Transform>(entity);

	if (componentRegistry.HasComponent<Moveable>(entity)) {

		switch (eventMessage) {
		case EntityEvent::COLLISION: 
			transform->velocity *= -1.0f;
			break;
		
		default:
			break;
		}
	}	
}














