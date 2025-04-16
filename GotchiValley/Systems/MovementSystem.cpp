#include "MovementSystem.h"


using namespace GotchiValley;

void MovementSystem::Update() {
	
	auto controlArray = componentRegistry.GetComponentArray<MovementBehaviour>();
	for (auto i = controlArray.begin(); i != controlArray.end(); i++) {

		i->second->Update();
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