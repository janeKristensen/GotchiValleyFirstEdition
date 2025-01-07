#pragma once
#include "IObserver.h"

class GameWorld : public ISubject {
public:

	void AddObserver(IObserver* observer) override;
	void RemoveObserver(IObserver* observer) override;
	void NotifyObservers(Entity& entity, const sf::Event& event) override;
	void PollEvents(Entity& entity, std::shared_ptr<sf::RenderWindow> window);
private:
	std::list<IObserver*> mObservers;
};