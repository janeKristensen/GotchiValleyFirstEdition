#pragma once
#include "SFML/Graphics.hpp"


class IObserver {
public:
	virtual ~IObserver() {};
	virtual void OnNotify(const sf::Event& event, std::string message) = 0;
};

class ISubject{
public:
	virtual ~ISubject() {};
	virtual void AddObserver(IObserver* observer) = 0;
	virtual void RemoveObserver(IObserver* observer) = 0;
	virtual void NotifyObservers(const sf::Event& event, std::string message) = 0;
};
