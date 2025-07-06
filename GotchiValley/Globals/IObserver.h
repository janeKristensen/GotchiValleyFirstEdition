#pragma once
#include "Components.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"

namespace GotchiValley {

	/*class IWindowObserver {
	public:
		virtual ~IWindowObserver() {};
		virtual void OnNotify(const sf::Event& event, const std::string& message) = 0;
	};

	class IWindowSubject {
	public:
		virtual ~IWindowSubject() {};
		virtual void AddObserver(IWindowObserver* observer) = 0;
		virtual void RemoveObserver(IWindowObserver* observer) = 0;
		virtual void NotifyObservers(const sf::Event& event, const std::string& message) const = 0;
	};*/

	class IGameObserver {
	public:
		virtual ~IGameObserver() {};
		virtual void onNotify(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) = 0;
	};

	class IGameSubject {
	public:
		virtual ~IGameSubject() {};
		virtual void addObserver(IGameObserver* observer) = 0;
		virtual void removeObserver(IGameObserver* observer) = 0;
		virtual void notifyObservers(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) const = 0;
	};

}

