#include "CollisionSystem.h"
#include <iostream>


using namespace GotchiValley;

void CollisionSystem::Update() {

	auto colliderArray = componentRegistry.GetComponentArray<Collider>();
	std::cout << colliderArray.size();

	for (auto i = colliderArray.begin(); i != colliderArray.end(); i++) {

		if (componentRegistry.HasComponent<Moveable>(i->first)) {

			for (auto j = colliderArray.begin(); j != colliderArray.end(); j++) {

				if (i == j) continue;
				
				ResolveCollision({ i->first, i->second }, { j->first, j->second });

				// only player can interact with objects
				auto player = componentRegistry.GetComponentOfType<Controlable>(i->first);
				if (!player) continue;
				ResolveInteractions({ i->first, i->second }, { j->first, j->second });
			}
		}
	}
}

void CollisionSystem::ResolveCollision(const std::pair<const Entity, const std::shared_ptr<Collider>>& entity, const std::pair<const Entity, const std::shared_ptr<Collider>>& other) const {

	if (entity.second->boundingBox.findIntersection(other.second->boundingBox))
	{
		NotifyObservers(entity.first, EntityEvent::COLLISION);
		NotifyObservers(other.first, EntityEvent::COLLISION);
	}	
		
}

void CollisionSystem::ResolveInteractions(const std::pair<const Entity, const std::shared_ptr<Collider>>& entity, const std::pair<const Entity, const std::shared_ptr<Collider>>& other) const {

	auto interactable = componentRegistry.GetComponentOfType<Interactable>(other.first);
	if (!interactable) return;

	sf::Vector2f size = {
		entity.second->boundingBox.size.x * 3, 
		entity.second->boundingBox.size.y * 3
	};
	sf::Vector2f position = { 
		static_cast<float>(entity.second->boundingBox.position.x - size.x / 3), 
		static_cast<float>(entity.second->boundingBox.position.y - size.y / 3) 
	};
	sf::FloatRect activeArea = { position, size };
	activeArea.findIntersection(other.second->boundingBox) ? interactable->interactionActive = true : interactable->interactionActive = false;
}

void CollisionSystem::AddObserver(IGameObserver* observer) {

	mObservers.emplace(observer);
}

void CollisionSystem::RemoveObserver(IGameObserver* observer) {

	mObservers.erase(observer);
}

void CollisionSystem::NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const {

	for (auto observer : mObservers) {
		observer->OnNotify(entity, eventMessage);
	}
}