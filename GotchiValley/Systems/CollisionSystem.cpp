#include "CollisionSystem.h"


using namespace GotchiValley;

void CollisionSystem::Update() {

	auto colliderArray = componentRegistry.GetComponentArray<Collider>();

	for (auto i = colliderArray.begin(); i != colliderArray.end(); i++) {

		if (componentRegistry.HasComponent<Moveable>(i->first)) {

			for (auto j = colliderArray.begin(); j != colliderArray.end(); j++) {

				if (i == j) continue;

				if (i->second->boundingBox.findIntersection(j->second->boundingBox))
				{
					NotifyObservers(i->first, EntityEvent::COLLISION);
					NotifyObservers(j->first, EntityEvent::COLLISION);
					i->second->hasCollided = true;
					j->second->hasCollided = true;
				}
			}
		}
	}
}


void CollisionSystem::AddObserver(IGameObserver* observer) {

	mObservers.emplace(observer);
}

void CollisionSystem::RemoveObserver(IGameObserver* observer) {

	mObservers.erase(observer);
}

void CollisionSystem::NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) {

	for (auto observer : mObservers) {
		observer->OnNotify(entity, eventMessage);
	}
}