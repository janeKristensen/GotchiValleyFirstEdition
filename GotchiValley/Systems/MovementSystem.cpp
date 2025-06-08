#include "MovementSystem.h"
#include <random>


using namespace GotchiValley;

void MovementSystem::Update(float& dt) {
	
	auto controlArray = componentRegistry.GetComponentArray<Controlable>();
	auto followArray = componentRegistry.GetComponentArray<FollowBehaviour>();
	auto roamArray = componentRegistry.GetComponentArray<RoamBehaviour>();
	
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
	}

	
	SetFollowPath(followArray);
	FollowToNode(followArray, dt);

	SetRoamPath(roamArray);
	RoamToNode(roamArray, dt);
}

void MovementSystem::SetFollowPath(const std::unordered_map<Entity, std::shared_ptr<FollowBehaviour>>& followArray) {

	for (auto i = followArray.begin(); i != followArray.end(); i++) {

		if (!i->second->isFollowActive) continue;

		auto entityActor = componentRegistry.GetComponentOfType<Transform>(i->first);
		auto entityDest = componentRegistry.GetComponentOfType<Transform>(i->second->entity);

		Node actor;
		actor.x = (entityActor->position.x + TILE_SIZE.x / 2) / TILE_SIZE.x;
		actor.y = (entityActor->position.y + TILE_SIZE.y / 2) / TILE_SIZE.y;

		Node destination;
		destination.x = (entityDest->position.x + TILE_SIZE.x / 2) / TILE_SIZE.x;
		destination.y = (entityDest->position.y + TILE_SIZE.y / 2) / TILE_SIZE.y;

		i->second->path = Pathfinder::FindPath(actor, destination);
		i->second->hasPath = true;
	}
}

void MovementSystem::SetRoamPath(const std::unordered_map<Entity, std::shared_ptr<RoamBehaviour>>& roamArray) {

	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0, 25);

	for (auto i = roamArray.begin(); i != roamArray.end(); i++) {

		if (!i->second->isRoamActive || (i->second->hasPath && !i->second->path.empty())) continue;

		auto entityActor = componentRegistry.GetComponentOfType<Transform>(i->first);

		Node actor;
		actor.x = (entityActor->position.x + TILE_SIZE.x / 2) / TILE_SIZE.x;
		actor.y = (entityActor->position.y + TILE_SIZE.y / 2) / TILE_SIZE.y;

		Node destination;
		uint32_t randomX = std::floor(dist(e2));
		uint32_t randomY = std::floor(dist(e2));
		destination.x = randomX;
		destination.y = randomY;
		std::cout << randomX << " " << randomY << std::endl;

		i->second->path = Pathfinder::FindPath(actor, destination);
		i->second->hasPath = true;
	}
}

void MovementSystem::FollowToNode(const std::unordered_map<Entity, std::shared_ptr<FollowBehaviour>>& followArray, const float& dt) {

	for (auto i = followArray.begin(); i != followArray.end(); i++) {

		if (!i->second->isFollowActive || !i->second->hasPath || i->second->path.empty()) continue;

		if (i->second->currentStep < i->second->path.size() - 1) {

			auto entityActor = componentRegistry.GetComponentOfType<Transform>(i->first);
			auto entityDest = componentRegistry.GetComponentOfType<Transform>(i->second->entity);
			const std::shared_ptr<Node>& node = i->second->path[i->second->currentStep];

			sf::Vector2f targetPos{ static_cast<float>(node->x * TILE_SIZE.x), static_cast<float>(node->y * TILE_SIZE.y) };

			sf::Vector2f direction = targetPos - entityActor->position;
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			if (distance > 0.1f) { // Still moving toward node
				entityActor->velocity = direction / distance;
				entityActor->position += entityActor->velocity * dt * entityActor->speed;

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
			i->second->currentStep = 0;
		}
	}
}

void MovementSystem::RoamToNode(const std::unordered_map<Entity, std::shared_ptr<RoamBehaviour>>& roamArray, const float& dt) {

	for (auto i = roamArray.begin(); i != roamArray.end(); i++) {

		if (!i->second->isRoamActive || !i->second->hasPath || i->second->path.empty()) continue;

		if (i->second->currentStep < i->second->path.size() - 1) {

			auto entityActor = componentRegistry.GetComponentOfType<Transform>(i->first);
			const std::shared_ptr<Node>& node = i->second->path[i->second->currentStep];

			sf::Vector2f targetPos{ static_cast<float>(node->x * TILE_SIZE.x), static_cast<float>(node->y * TILE_SIZE.y) };

			sf::Vector2f direction = targetPos - entityActor->position;
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			if (distance > 0.1f) { // Still moving toward node
				entityActor->velocity = direction / distance;
				entityActor->position += entityActor->velocity * dt * entityActor->speed;

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
			i->second->currentStep = 0;
		}
	}
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