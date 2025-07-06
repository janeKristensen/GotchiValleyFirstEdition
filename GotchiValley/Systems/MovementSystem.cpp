#include "MovementSystem.h"
#include <random>


using namespace GotchiValley;

void MovementSystem::update(float& dt) {

	auto entityArray = mGameWorld.getEntities();
	
	for (auto i = 0; i < entityArray.size(); i++) {

		if (entityArray[i] != nullptr && entityArray[i]->isEntityAlive()) {

			auto creature = std::dynamic_pointer_cast<Creature>(entityArray[i]);
			if (creature && creature->isMoveable()) {

				Transform transform = entityArray[i]->getTransform();
				State& entityState = entityArray[i]->getState();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

					transform.velocity.y = -mAcceleration;
					entityState = State::RUNNING;
					notifyObservers(entityArray[i], EntityEvent::MOVE_UP);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

					transform.velocity.y = mAcceleration;
					entityState = State::RUNNING;
					notifyObservers(entityArray[i], EntityEvent::MOVE_DOWN);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

					transform.velocity.x = mAcceleration;
					entityState = State::RUNNING;
					notifyObservers(entityArray[i], EntityEvent::MOVE_LEFT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

					transform.velocity.x = -mAcceleration;
					entityState = State::RUNNING;
					notifyObservers(entityArray[i], EntityEvent::MOVE_RIGHT);
				}

				setFollowPath(creature, dt);
			}
		}
	}
}

void MovementSystem::setFollowPath(std::shared_ptr<Creature>& creature, const float& dt) {

	std::shared_ptr<FollowBehaviour> followBehaviour = creature->getFollowBehaviour();
	Transform transform = creature->getTransform();

	Node actor;
	Node destination;
	actor.x = (transform.position.x + TILE_SIZE.x / 2) / TILE_SIZE.x;
	actor.y = (transform.position.y + TILE_SIZE.y / 2) / TILE_SIZE.y;

	if (followBehaviour->isFollowActive) {

		destination.x = (followBehaviour->entity->getTransform().position.x + TILE_SIZE.x / 2) / TILE_SIZE.x;
		destination.y = (followBehaviour->entity->getTransform().position.y + TILE_SIZE.y / 2) / TILE_SIZE.y;

		followBehaviour->path = Pathfinder::findPath(actor, destination);
		followBehaviour->hasPath = true;
		creature->setFollowBehaviour(followBehaviour);
	}
	else {

		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_real_distribution<> dist(0, 25);

		uint32_t randomX = std::floor(dist(e2));
		uint32_t randomY = std::floor(dist(e2));
		destination.x = randomX;
		destination.y = randomY;
		std::cout << randomX << " " << randomY << std::endl;

		followBehaviour->path = Pathfinder::findPath(actor, destination);
		followBehaviour->hasPath = true;
		creature->setFollowBehaviour(followBehaviour);
	}

	if (followBehaviour->currentStep < followBehaviour->path.size() - 1) {

		const std::shared_ptr<Node>& node = followBehaviour->path[followBehaviour->currentStep];

		sf::Vector2f targetPos{ static_cast<float>(node->x * TILE_SIZE.x), static_cast<float>(node->y * TILE_SIZE.y) };

		sf::Vector2f direction = targetPos - transform.position;
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance > 0.1f) { // Still moving toward node
			transform.velocity = direction / distance;
			transform.position += transform.velocity * dt * transform.speed;

			// Optional: clamp to prevent overshoot
			if (std::abs(transform.position.x - targetPos.x) < 1.0f &&
				std::abs(transform.position.y - targetPos.y) < 1.0f) {
				transform.position = targetPos;
				followBehaviour->currentStep++;
			}
		}
		else {
			// Reached target node
			transform.position = targetPos;
			followBehaviour->currentStep++;
		}

		creature->setTransform(transform);
	}
	else {
		followBehaviour->hasPath = false;
		followBehaviour->currentStep = 0;
	}
	
}



//void MovementSystem::followToNode(std::shared_ptr<Creature>& creature, const float& dt) {
//
//	for (auto i = followArray.begin(); i != followArray.end(); i++) {
//
//		if (!i->second->isFollowActive || !i->second->hasPath || i->second->path.empty()) continue;
//
//		if (i->second->currentStep < i->second->path.size() - 1) {
//
//			auto entityActor = componentRegistry.GetComponentOfType<Transform>(i->first);
//			auto entityDest = componentRegistry.GetComponentOfType<Transform>(i->second->entity);
//			const std::shared_ptr<Node>& node = i->second->path[i->second->currentStep];
//
//			sf::Vector2f targetPos{ static_cast<float>(node->x * TILE_SIZE.x), static_cast<float>(node->y * TILE_SIZE.y) };
//
//			sf::Vector2f direction = targetPos - entityActor->position;
//			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//
//			if (distance > 0.1f) { // Still moving toward node
//				entityActor->velocity = direction / distance;
//				entityActor->position += entityActor->velocity * dt * entityActor->speed;
//
//				// Optional: clamp to prevent overshoot
//				if (std::abs(entityActor->position.x - targetPos.x) < 1.0f &&
//					std::abs(entityActor->position.y - targetPos.y) < 1.0f) {
//					entityActor->position = targetPos;
//					i->second->currentStep++;
//				}
//			}
//			else {
//				// Reached target node
//				entityActor->position = targetPos;
//				i->second->currentStep++;
//			}
//		}
//		else {
//			i->second->hasPath = false;
//			i->second->currentStep = 0;
//		}
//	}
//}


void MovementSystem::addObserver(IGameObserver* observer) {

	mObservers.emplace(observer);
}

void MovementSystem::removeObserver(IGameObserver* observer) {

	mObservers.erase(observer);
}

void MovementSystem::notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const{

	for (auto observer : mObservers) {
		observer->onNotify(entity, eventMessage);
	}
}