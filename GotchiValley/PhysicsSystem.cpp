#include "PhysicsSystem.h"

using namespace GotchiValley;
extern const size_t MAX_ENTITIES;

void PhysicsSystem::Update(ComponentManager<Transform>& transformManager, ComponentManager<sf::Sprite>& spriteManager, ComponentManager<Collider>& colliderManager, float dt) {

	for (uint32_t i = 0; i < MAX_ENTITIES; i++) {

		if (!transformManager.HasComponent(i)) continue;
		auto transform = transformManager.GetComponentOfType(i);
		transform->position += transform->velocity * dt * transform->speed;
	
		if (!spriteManager.HasComponent(i)) continue;
		auto sprite = spriteManager.GetComponentOfType(i);
		sprite->setPosition(transform->position);

		if (!colliderManager.HasComponent(i)) continue;
		auto collider = colliderManager.GetComponentOfType(i);
		collider->boundingBox.position = transform->position;

		transform->velocity = .95f * transform->velocity;	
	}
}

void PhysicsSystem::SetPosition(ComponentManager<Transform>& transformManager, Entity entity, sf::Vector2f position) {

	if (transformManager.HasComponent(entity)) {

		auto transform = transformManager.GetComponentOfType(entity);
		transform->position = position;
	}	
}












