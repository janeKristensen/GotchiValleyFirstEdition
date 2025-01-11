#include "UISystem.h"


UISystem::UISystem(std::shared_ptr<sf::RenderWindow> window, ISubject& subject) : mWindow(window), mSubject(subject) {

	this->mSubject.AddObserver(this);
}

void UISystem::OnNotify(const sf::Event& event, const std::string& message) {

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