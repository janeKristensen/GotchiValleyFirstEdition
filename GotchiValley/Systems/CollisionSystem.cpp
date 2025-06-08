#include "CollisionSystem.h"
#include <iostream>


using namespace GotchiValley;

void CollisionSystem::Update() {

	std::vector<CollisionData> collisions;

	auto colliderArray = componentRegistry.GetComponentArray<Collider>();

	for (auto i = colliderArray.begin(); i != colliderArray.end(); i++) {

		auto entityState = componentRegistry.GetComponentOfType<EntityState>(i->first);

		if (entityState && entityState->state != State::COLLIDING) {
			if (componentRegistry.HasComponent<Moveable>(i->first)) {

				// Chack if entity is colliding with the walls.
				if (i->second->boundingBox.position.x < 0 ||
					i->second->boundingBox.position.y < 0 ||
					i->second->boundingBox.position.x > SCREEN_SIZE.x - i->second->boundingBox.size.x ||
					i->second->boundingBox.position.y > SCREEN_SIZE.y - i->second->boundingBox.size.y) {

					NotifyObservers(i->first, EntityEvent::COLLISION);
					//entityState->state = State::IDLE;
					entityState->state = State::COLLIDING;
				}

				// Check for collision with other entities.
				for (auto j = colliderArray.begin(); j != colliderArray.end(); j++) {

					if (i == j) continue;

					if (i->second->boundingBox.findIntersection(j->second->boundingBox))
					{
						collisions.push_back(CollisionData{ i->first, i->second, j->first, j->second });
						entityState->state = State::COLLIDING;
					}
				}

				/* Check for collision with map components. 
				
					TODO: this should only check for collisions with currently loaded map!
				*/
				auto levelArray = componentRegistry.GetComponentArray<Level>();

				for (auto k = levelArray.begin(); k != levelArray.end(); k++) {

					for (auto l = k->second->colliders.begin(); l != k->second->colliders.end(); l++) {

						Collider* collider = l->get();


						if (i->second->boundingBox.findIntersection(collider->boundingBox)) {

							collisions.push_back(CollisionData{ i->first, i->second, k->first, *l });
							entityState->state = State::COLLIDING;
							break;
						}

					}
				}
			}
		}
	}

	ResolveCollision(collisions);
}

void CollisionSystem::ResolveCollision(const std::vector<CollisionData>& collisions) const {

	for (auto i = collisions.begin(); i != collisions.end(); i++) {

		ResolveInteractions(i->entity, i->entityCollider, i->other, i->otherCollider);

		NotifyObservers(i->entity, EntityEvent::COLLISION);

		auto entityState = componentRegistry.GetComponentOfType<EntityState>(i->entity);
		entityState->state = State::IDLE;

	}
}

void CollisionSystem::ResolveInteractions(const Entity& entity, const std::shared_ptr<Collider>& entityCollider, const Entity& other, const std::shared_ptr<Collider>& otherCollider) const {

	// only player can interact with objects
	auto player = componentRegistry.GetComponentOfType<Controlable>(entity);
	if (!player) return;

	auto interactable = componentRegistry.GetComponentOfType<Interactable>(other);
	if (!interactable) return;

	sf::Vector2f size = {
		entityCollider->boundingBox.size.x * 3,
		entityCollider->boundingBox.size.y * 3
	};
	sf::Vector2f position = {
		static_cast<float>(entityCollider->boundingBox.position.x - size.x / 3),
		static_cast<float>(entityCollider->boundingBox.position.y - size.y / 3)
	};
	sf::FloatRect activeArea = { position, size };
	activeArea.findIntersection(otherCollider->boundingBox) ? interactable->interactionActive = true : interactable->interactionActive = false;
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