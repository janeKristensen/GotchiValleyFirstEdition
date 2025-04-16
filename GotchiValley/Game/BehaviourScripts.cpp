#include "BehaviourScripts.h"

namespace GotchiValley {

	MovementBehaviour playerMovement(player,
		[player]() {

			auto entityTransform = componentRegistry.GetComponentOfType<Transform>(player);
			auto entityAnimation = componentRegistry.GetComponentOfType<Animation>(player);


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

				entityTransform->velocity.y = -1.f;
				entityAnimation->animName = AnimationName::RUNNING;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

				entityTransform->velocity.y = 1.f;
				entityAnimation->animName = AnimationName::RUNNING;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

				entityTransform->velocity.x = 1.f;
				entityAnimation->animName = AnimationName::RUNNING;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

				entityTransform->velocity.x = -1.f;
				entityAnimation->animName = AnimationName::RUNNING;
			}
			else {
				entityTransform->velocity.x = 0.f;
				entityAnimation->animName = AnimationName::IDLE;
				entityAnimation->frameNum = 0;
			}
		}
	);

};