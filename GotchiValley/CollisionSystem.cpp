#include "CollisionSystem.h"


using namespace GotchiValley;

void CollisionSystem::Update() {

	auto colliderArray = componentRegistry.GetComponentArray<Collider>();
	for (auto i = colliderArray.begin(); i != colliderArray.end(); i++) {

		for (auto j = colliderArray.begin(); j != colliderArray.end(); j++) {

			if (j == i) continue;

			if (i->second->boundingBox.findIntersection(j->second->boundingBox))
			{
				if (componentRegistry.HasComponent<Moveable>(i->first)) {

					auto transform = componentRegistry.GetComponentOfType<Transform>(i->first);
					transform->velocity *= -1.f;
				}
			}
		}
	}
}