#include "MovementSystem.h"
#include "GameWorld.h"


using namespace GotchiValley;

void MovementSystem::update(float& dt) {

	std::array<std::shared_ptr<Entity>, MAX_ENTITIES>& entityArray = mGameWorld.getEntities();
	
	for (auto i = 0; i < entityArray.size(); i++) {

		if (entityArray[i] == nullptr) break;
		if(!entityArray[i]->isEntityAlive()) continue;

		std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(entityArray[i]);
		if (player && player->isMoveable()) {

			Transform& transform = entityArray[i]->getTransform();
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

			entityArray[i]->setTransform(transform);
		}
		else {

			std::shared_ptr<Creature> creature = std::dynamic_pointer_cast<Creature>(entityArray[i]);
			if (creature) {
				updateFollowPath(creature, dt);
				creature->update();
			}
		}
		
	}
}

void MovementSystem::updateFollowPath(std::shared_ptr<Creature>& creature, const float& dt) {

	std::shared_ptr<FollowBehaviour> followBehaviour = creature->getFollowBehaviour();
	Transform& transform = creature->getTransform();

	Node actor;
	Node destination;
	actor.x = (transform.position.x + TILE_SIZE.x / 2) / TILE_SIZE.x;
	actor.y = (transform.position.y + TILE_SIZE.y / 2) / TILE_SIZE.y;

	if (followBehaviour->isFollowActive) {
		destination.x = (followBehaviour->entity->getTransform().position.x + TILE_SIZE.x / 2) / TILE_SIZE.x;
		destination.y = (followBehaviour->entity->getTransform().position.y + TILE_SIZE.y / 2) / TILE_SIZE.y;

		creature->setFollowPath(Pathfinder::findPath(actor, destination));
	}
	else if(followBehaviour->path.empty() || followBehaviour->hasPath == false) {

		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_real_distribution<> dist(0, 25);

		uint32_t randomX = std::floor(dist(e2));
		uint32_t randomY = std::floor(dist(e2));
		destination.x = randomX;
		destination.y = randomY;
		std::cout << randomX << " " << randomY << std::endl;

		creature->setFollowPath(Pathfinder::findPath(actor, destination));
	}

	if (followBehaviour->currentStep < followBehaviour->path.size() - 2) {

			const std::shared_ptr<Node>& node = followBehaviour->path[followBehaviour->currentStep];

			sf::Vector2f targetPos{ static_cast<float>(node->x * TILE_SIZE.x), static_cast<float>(node->y * TILE_SIZE.y)};
			sf::Vector2f direction = targetPos - transform.position;
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			if (distance > 25.f) { // Still moving toward node
				transform.velocity = direction / distance;
				transform.position += transform.velocity * dt * transform.speed;
			}
			else {

				followBehaviour->currentStep++;
			}

			creature->setTransform(transform);
			creature->setFollowBehaviour(followBehaviour);
	}
	else {
		followBehaviour->hasPath = false;
		followBehaviour->currentStep = 0;
		creature->setFollowBehaviour(followBehaviour);
	}
}


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