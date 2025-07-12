#include "CollisionSystem.h"



using namespace GotchiValley;

void CollisionSystem::update() {

	auto entityArray = mGameWorld.getEntities();
	mCollisions = std::vector<CollisionData>();

	for (auto i = 0; i < entityArray.size(); i++) {

		if (entityArray[i] != nullptr && entityArray[i]->isEntityAlive() && entityArray[i]->getState() != State::COLLIDING) {

			auto creature = std::dynamic_pointer_cast<Creature>(entityArray[i]);
			if (creature) {

				if (creature->isMoveable()) {

					Collider collider = creature->getCollider();
					// Chack if entity is colliding with the walls.
					if (collider.boundingBox.position.x < 0 ||
						collider.boundingBox.position.y < 0 ||
						collider.boundingBox.position.x > SCREEN_SIZE.x - collider.boundingBox.size.x ||
						collider.boundingBox.position.y > SCREEN_SIZE.y - collider.boundingBox.size.y) {

						notifyObservers(entityArray[i], EntityEvent::COLLISION);
						entityArray[i]->setState(State::COLLIDING);
					}

					// Check for collision with other entities.
					for (auto j = 0; j < entityArray.size(); j++) {

						if (entityArray[j] == nullptr) break;
						if (i == j) continue;

						auto other = std::dynamic_pointer_cast<Creature>(entityArray[j]);
						if (other) {

							Collider otherCollider = other->getCollider();

							if (collider.boundingBox.findIntersection(otherCollider.boundingBox))
							{
								mCollisions.push_back(CollisionData{ entityArray[i], collider, entityArray[j], otherCollider});
								entityArray[i]->setState(State::COLLIDING);
							}
						}
					}

					// Check for collision with map components.

					std::shared_ptr<Level> level = mGameWorld.getCurrentLevel();

					for (auto l = level->colliders.begin(); l != level->colliders.end(); l++) {

						if (collider.boundingBox.findIntersection(l->get()->boundingBox)) {

							Collider& otherCollider = *l->get();
							/* 
							Player entity passed in twice as sub for other entity.
							Needs a proper fix 
							*/
							mCollisions.push_back(CollisionData{ entityArray[i], collider, entityArray[i], otherCollider});
							entityArray[i]->setState(State::COLLIDING);
							break;
						}
					}
				}
			}
		}
	}

	resolveCollision(mCollisions);
}

void CollisionSystem::resolveCollision(std::vector<CollisionData>& collisions)  {

	for (auto i = collisions.begin(); i != collisions.end(); i++) {

		// only player can interact with objects
		auto player = std::dynamic_pointer_cast<Player>(i->entity);
		auto otherEntity = std::dynamic_pointer_cast<Creature>(i->other);
		if (!player) continue;

		sf::Vector2f size = {
			i->entityCollider.boundingBox.size.x * 3,
			i->entityCollider.boundingBox.size.y * 3
		};
		sf::Vector2f position = {
			static_cast<float>(i->entityCollider.boundingBox.position.x - size.x / 3),
			static_cast<float>(i->entityCollider.boundingBox.position.y - size.y / 3)
		};
		sf::FloatRect activeArea = { position, size };

		if (otherEntity) {

			activeArea.findIntersection(i->otherCollider.boundingBox) ? otherEntity->setInteractive(true) : otherEntity->setInteractive(false);
		}
		
		notifyObservers(i->entity, EntityEvent::COLLISION);
		i->entity->setState(State::IDLE);
	}
}


void CollisionSystem::addObserver(IGameObserver* observer) {

	mObservers.emplace(observer);
}

void CollisionSystem::removeObserver(IGameObserver* observer) {

	mObservers.erase(observer);
}

void CollisionSystem::notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const {

	for (auto observer : mObservers) {
		observer->onNotify(entity, eventMessage);
	}
}