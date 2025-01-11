#include "CollisionSystem.h"
#include <iostream>

using namespace GotchiValley;

void CollisionSystem::Update(ComponentManager<Transform>& transformManager, ComponentManager<Collider>& colliderManager, ComponentManager<Moveable>& movementManager) {

	auto colliderArray = colliderManager.GetComponentArray();
	for (auto i = colliderArray.begin(); i != colliderArray.end(); i++) {

		for (auto j = colliderArray.begin(); j != colliderArray.end(); j++) {

			if (j == i) continue;

			if (i->second->boundingBox.findIntersection(j->second->boundingBox))
			{
				if (movementManager.HasComponent(i->first)) {

					auto transform = transformManager.GetComponentOfType(i->first);
					transform->velocity *= -1.f;
				}
			}
		}
	}
}