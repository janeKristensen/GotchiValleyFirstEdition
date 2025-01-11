#pragma once
#include "IObserver.h"

namespace GotchiValley {

	class GameWorld : public ISubject {
	public:

		void AddObserver(IObserver* observer) override;
		void RemoveObserver(IObserver* observer) override;
		void NotifyObservers(const sf::Event& event, const std::string& message) override;
		void PollEvents(std::shared_ptr<sf::RenderWindow> window);

	private:
		std::list<IObserver*> mObservers;
	};

}

