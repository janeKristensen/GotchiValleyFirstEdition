#pragma once
#include "SFML/Graphics.hpp"
#include "GotchiValley.h"
#include "EntityManager.h"
#include "Entity.h"


class IObserver {
public:
	virtual ~IObserver() {};
	virtual void OnNotify(EntityManager& manager, const sf::Event& event, std::string message) = 0;
};

class ISubject{
public:
	virtual ~ISubject() {};
	virtual void AddObserver(IObserver* observer) = 0;
	virtual void RemoveObserver(IObserver* observer) = 0;
	virtual void NotifyObservers(EntityManager& manager, const sf::Event& event, std::string message) = 0;
};
