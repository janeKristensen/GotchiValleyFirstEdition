#include "CollisionSystem.h"
#include <iostream>

using namespace GotchiValley;

void CollisionSystem::Update(ComponentManager<Transform>& transformManager, ComponentManager<Collider>& colliderManager, ComponentManager<Moveable>& movementManager) {

	for (uint32_t i = 1; i < MAX_ENTITIES; i++) {

		for (uint32_t j = 2; j < MAX_ENTITIES; j++) {

			if (!colliderManager.HasComponent(i)) continue;
			auto collider1 = colliderManager.GetComponentOfType(i);

			if (!colliderManager.HasComponent(j)) continue;
			auto collider2 = colliderManager.GetComponentOfType(j);

			if (collider1->boundingBox.findIntersection(collider2->boundingBox))
			{
				if (movementManager.HasComponent(i)) {

					auto transform = transformManager.GetComponentOfType(i);
					transform->velocity *= -1.f;
				}
			}
		}
	}
}