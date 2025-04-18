#include "MovementSystem.h"


using namespace GotchiValley;

void MovementSystem::Update() {
	
	auto controlArray = componentRegistry.GetComponentArray<Controlable>();
	
	for (auto i = controlArray.begin(); i != controlArray.end(); i++) {

		auto entityTransform = componentRegistry.GetComponentOfType<Transform>(i->first);
		auto entityState = componentRegistry.GetComponentOfType<EntityState>(i->first);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

			entityTransform->velocity.y = -mAcceleration;
			entityState->state == State::RUNNING;
			NotifyObservers(i->first, EntityEvent::MOVE_UP);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

			entityTransform->velocity.y = mAcceleration;
			entityState->state == State::RUNNING;
			NotifyObservers(i->first, EntityEvent::MOVE_DOWN);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

			entityTransform->velocity.x = mAcceleration;
			entityState->state == State::RUNNING;
			NotifyObservers(i->first, EntityEvent::MOVE_LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

			entityTransform->velocity.x = -mAcceleration;
			entityState->state == State::RUNNING;
			NotifyObservers(i->first, EntityEvent::MOVE_RIGHT);
		}
		else {
			entityState->state == State::IDLE;
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