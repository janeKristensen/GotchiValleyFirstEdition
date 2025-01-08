#include "UISystem.h"


UISystem::UISystem(std::shared_ptr<sf::RenderWindow> window, ISubject& subject) : mWindow(window), mSubject(subject) {

	this->mSubject.AddObserver(this);
}

void UISystem::OnNotify(EntityManager& manager, const sf::Event& event) {

	if (event.is<sf::Event::Closed>()) {
		mWindow->close();
	}
	else if (event.is<sf::Event::KeyPressed>()) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			mWindow->close();
		}
	}
	
}

void UISystem::RemoveFromSubject() {
	mSubject.RemoveObserver(this);
}