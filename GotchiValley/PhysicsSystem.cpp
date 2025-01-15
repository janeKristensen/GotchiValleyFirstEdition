#include "Components.h"
#include "SharedObjects.h"
#include "PhysicsSystem.h"

using namespace GotchiValley;
//extern const size_t MAX_ENTITIES;

void PhysicsSystem::Update(float& dt) {

	auto transformArray = componentRegistry.GetComponentArray<Transform>();

	for (auto i = transformArray.begin(); i != transformArray.end(); i++) {

		auto transform = i->second;

		transform->position += transform->velocity * dt * transform->speed;
	
		auto sprite = componentRegistry.GetComponentOfType<sf::Sprite>(i->first);
		if (!sprite) continue;
		sprite->setPosition(transform->position);

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
	
}












