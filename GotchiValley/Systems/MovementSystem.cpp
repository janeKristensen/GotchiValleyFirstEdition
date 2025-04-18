#include "MovementSystem.h"


using namespace GotchiValley;

void MovementSystem::Update(float& dt) {
	
	auto controlArray = componentRegistry.GetComponentArray<Controlable>();
	
	for (auto i = controlArray.begin(); i != controlArray.end(); i++) {

		auto entityTransform = componentRegistry.GetComponentOfType<Transform>(i->first);
		auto entityState = componentRegistry.GetComponentOfType<EntityState>(i->first);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

			entityTransform->velocity.y = -mAcceleration;
			entityState->state = State::RUNNING;
			NotifyObservers(i->first, EntityEvent::MOVE_UP);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

			entityTransform->velocity.y = mAcceleration;
			entityState->state = State::RUNNING;
			NotifyObservers(i->first, EntityEvent::MOVE_DOWN);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

			entityTransform->velocity.x = mAcceleration;
			entityState->state = State::RUNNING;
			NotifyObservers(i->first, EntityEvent::MOVE_LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

			entityTransform->velocity.x = -mAcceleration;
			entityState->state = State::RUNNING;
			NotifyObservers(i->first, EntityEvent::MOVE_RIGHT);
		}
		else {
			entityState->state = State::IDLE;
		}
	}

	auto followArray = componentRegistry.GetComponentArray<FollowBehaviour>();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {

		for (auto i = followArray.begin(); i != followArray.end(); i++) {

			auto entityActor = componentRegistry.GetComponentOfType<Transform>(i->first);
			auto entityDest = componentRegistry.GetComponentOfType<Transform>(i->second->entity);

			Node actor;
			actor.x = entityActor->position.x / TILE_SIZE.x;
			actor.y = entityActor->position.y / TILE_SIZE.y;

			Node destination;
			destination.x = entityDest->position.x / TILE_SIZE.x;
			destination.y = entityDest->position.y / TILE_SIZE.y;

			i->second->path = Pathfinder::FindPath(actor, destination);
			i->second->hasPath = true;
		}
	}

	for (auto i = followArray.begin(); i != followArray.end(); i++) {
	
		if (!i->second->hasPath || i->second->path.empty()) continue;

		if (i->second->currentStep < i->second->path.size()) {

			auto entityActor = componentRegistry.GetComponentOfType<Transform>(i->first);
			auto entityDest = componentRegistry.GetComponentOfType<Transform>(i->second->entity);
			const Node& node = i->second->path[i->second->currentStep];

			//sf::Vector2f currentPos{ entityActor->position.x, entityActor->position.y };
			sf::Vector2f targetPos{ static_cast<float>(node.x * TILE_SIZE.x), static_cast<float>(node.y * TILE_SIZE.y) };

			sf::Vector2f direction = targetPos - entityActor->position;
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			if (distance > 0.1f) { // Still moving toward node
				sf::Vector2f normalized = direction / distance;
				entityActor->position += normalized * entityActor->speed * dt;

				// Optional: clamp to prevent overshoot
				if (std::abs(entityActor->position.x - targetPos.x) < 1.0f &&
					std::abs(entityActor->position.y - targetPos.y) < 1.0f) {
					entityActor->position = targetPos;
					i->second->currentStep++;
				}
			}
			else {
				// Reached target node
				entityActor->position = targetPos;
				i->second->currentStep++;
			}
		}
		else {
			i->second->hasPath = false;
		}
	}
}

void MovementSystem::MoveToNode(Node actor, Node destination) {

	
}

void MovementSystem::AddObserver(IGameObserver* observer) {

	mObservers.emplace(observer);
}

void MovementSystem::RemoveObserver(IGameObserver* observer) {

	mObservers.erase(observer);
}

void MovementSystem::NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const{

	for (auto observer : mObservers) {
		observer->OnNotify(entity, eventMessage);
	}
}