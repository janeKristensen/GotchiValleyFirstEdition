#pragma once
#include "IObserver.h"
#include "EntityManager.h"

class GameWorld : public ISubject {
public:

	void AddObserver(IObserver* observer) override;
	void RemoveObserver(IObserver* observer) override;
	void NotifyObservers(EntityManager& manager, const sf::Event& event) override;
	void PollEvents(EntityManager& manager, std::shared_ptr<sf::RenderWindow> window);
private:
	std::list<IObserver*> mObservers;
};