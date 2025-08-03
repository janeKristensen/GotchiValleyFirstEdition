#include "AnimationSystem.h"
#include "GameWorld.h"
#include "Creature.h"

using namespace GotchiValley;


void AnimationSystem::update(float dt) {

	std::array<std::shared_ptr<Entity>, MAX_ENTITIES>& entityArray = mGameWorld.getEntities();

	for (auto i = 0; i < entityArray.size(); i++) {

		if (entityArray[i] == nullptr) break;

		Animation& animation = std::dynamic_pointer_cast<Drawable>(entityArray[i])->getAnimation();
		sf::Sprite& spriteComponent = std::dynamic_pointer_cast<Drawable>(entityArray[i])->getSprite();
		
		animation.frameTime += dt;

		if (animation.frameTime > (1 / animation.frames[animation.animName].animFPS)) {

			animation.frameNum += std::uint8_t(animation.frameTime * animation.frames[animation.animName].animFPS);

			if (animation.frameNum >= animation.frames[animation.animName].numFrames) {

				auto creature = std::dynamic_pointer_cast<Creature>(entityArray[i]);
				if (creature) {

					if (creature->getPhase() == CreaturePhase::UNEVOLVED) {

						animation.animName = AnimationName::INITIAL;
					}
					else if (creature && creature->getPhase() == CreaturePhase::EVOLVING) {

						creature->setPhase(CreaturePhase::EVOLVED);
						animation.animName = AnimationName::IDLE;
					}
				}
				else {
					animation.animName = AnimationName::IDLE;
				}
				
				animation.frameNum = animation.frameNum % animation.frames[animation.animName].numFrames;
			}
		}
		
		uint8_t imageNum = animation.startFrame + animation.frameNum;
		spriteComponent.setTextureRect(animation.frames[animation.animName].sprites[imageNum]);
		animation.frameTime = fmod(animation.frameTime, (1 / animation.frames[animation.animName].animFPS));
	}	
}


void AnimationSystem::onNotify(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) {

	auto drawable = std::dynamic_pointer_cast<Drawable>(entity);

	if (drawable) {

		Animation& animation = drawable->getAnimation();
		auto creature = std::dynamic_pointer_cast<Creature>(entity);

		switch (eventMessage) {

			case EntityEvent::COLLISION:
				animation.frameNum = 0;
				if (creature && creature->getPhase() == CreaturePhase::UNEVOLVED) {

					animation.animName = AnimationName::INITIAL;
				}
				else {

					animation.animName = AnimationName::COLLIDING;
				}
				break;

			case EntityEvent::INTERACTION:

				if (creature && creature->getPhase() == CreaturePhase::EVOLVING) {

					animation.animName = AnimationName::EVOLVING;
				}
				else {
					animation.animName = AnimationName::INTERACTING;
				}
				animation.frameNum = 0;
				entity->setInteractive(false);
				entity->setState(State::IDLE);
				break;

			case EntityEvent::MOVE_LEFT:

				if (animation.animName != AnimationName::RUNNING) {

					animation.animName = AnimationName::RUNNING;
					animation.frameNum = 0;
				}
				break;

			case EntityEvent::IDLE:
				animation.animName = AnimationName::IDLE;
				break;
		}
	}
}
		
	
