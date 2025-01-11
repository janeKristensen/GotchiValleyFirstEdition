#include "PhysicsSystem.h"

using namespace GotchiValley;
extern const size_t MAX_ENTITIES;

void PhysicsSystem::Update(ComponentManager<Transform>& transformManager, ComponentManager<sf::Sprite>& spriteManager, ComponentManager<Collider>& colliderManager, float& dt) {

	auto transformArray = transformManager.GetComponentArray();

	for (auto i = transformArray.begin(); i != transformArray.end(); i++) {

		auto transform = i->second;

		transform->position += transform->velocity * dt * transform->speed;
	
		auto sprite = spriteManager.GetComponentOfType(i->first);
		if (!sprite) continue;
		sprite->setPosition(transform->position);

		auto collider = colliderManager.GetComponentOfType(i->first);
		if (!collider) continue;
		collider->boundingBox.position = transform->position;

		transform->velocity = .95f * transform->velocity;	
	}
}

void PhysicsSystem::SetPosition(ComponentManager<Transform>& transformManager, Entity& entity, sf::Vector2f& position) {

	if (transformManager.HasComponent(entity)) {

		auto transform = transformManager.GetComponentOfType(entity);
		if (!transform) return;
		transform->position = position;
	}	
}












