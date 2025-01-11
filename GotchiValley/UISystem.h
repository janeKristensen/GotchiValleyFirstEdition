#pragma once
#include "IObserver.h"
#include "EntityManager.h"

class UISystem : public IObserver{
public:
	UISystem(std::shared_ptr<sf::RenderWindow> window, ISubject& subject);
	void OnNotify(const sf::Event& event, const std::string& message);
	void RemoveFromSubject();

private:
	std::shared_ptr<sf::RenderWindow> mWindow;
	ISubject& mSubject;
};

