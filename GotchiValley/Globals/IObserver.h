#pragma once
#include "Components.h"
#include "SFML/Graphics.hpp"

namespace GotchiValley {

	class IWindowObserver {
	public:
		virtual ~IWindowObserver() {};
		virtual void OnNotify(const sf::Event& event, const std::string& message) = 0;
	};

	class IWindowSubject {
	public:
		virtual ~IWindowSubject() {};
		virtual void AddObserver(IWindowObserver* observer) = 0;
		virtual void RemoveObserver(IWindowObserver* observer) = 0;
		virtual void NotifyObservers(const sf::Event& event, const std::string& message) = 0;
	};

	class IGameObserver {
	public:
		virtual ~IGameObserver() {};
		virtual void OnNotify(const Entity& entity, const EntityEvent& eventMessage) = 0;
	};

	class IGameSubject {
	public:
		virtual ~IGameSubject() {};
		virtual void AddObserver(IGameObserver* observer) = 0;
		virtual void RemoveObserver(IGameObserver* observer) = 0;
		virtual void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) = 0;
	};

}

