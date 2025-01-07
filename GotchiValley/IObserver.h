#pragma once
#include "SFML/Graphics.hpp"
#include "GotchiValley.h"
#include "Entity.h"


class IObserver {
public:
	virtual ~IObserver() {};
	virtual void OnNotify(Entity& entity, const sf::Event& event) = 0;
};

class ISubject{
public:
	virtual ~ISubject() {};
	virtual void AddObserver(IObserver* observer) = 0;
	virtual void RemoveObserver(IObserver* observer) = 0;
	virtual void NotifyObservers(Entity& entity, const sf::Event& event) = 0;
};
