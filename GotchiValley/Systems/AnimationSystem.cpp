#include "AnimationSystem.h"

using namespace GotchiValley;


void AnimationSystem::update(float dt) {

	auto entityArray = mGameWorld.getEntities();

	for (auto i = 0; i < entityArray.size(); i++) {

		if (entityArray[i] == nullptr) break;
		auto animation = std::dynamic_pointer_cast<Drawable>(entityArray[i])->getAnimation();
		auto spriteComponent = std::dynamic_pointer_cast<Drawable>(entityArray[i])->getSprite();
		auto entityState = entityArray[i]->getState();
		
		animation.frameTime += dt;

		if (animation.frameTime > (1 / animation.frames[animation.animName].animFPS)) {

			animation.frameNum += std::uint8_t(animation.frameTime * animation.frames[animation.animName].animFPS);

			if (animation.frameNum >= animation.frames[animation.animName].numFrames) {

				animation.animName = AnimationName::IDLE;
				animation.frameNum = animation.frameNum % animation.frames[animation.animName].numFrames;
			}
		}
		
		uint8_t imageNum = animation.startFrame + animation.frameNum;
		spriteComponent.sprite.setTextureRect(animation.frames[animation.animName].sprites[imageNum]);
		animation.frameTime = fmod(animation.frameTime, (1 / animation.frames[animation.animName].animFPS));
	}	
}


void AnimationSystem::onNotify(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) {

	auto drawable = std::dynamic_pointer_cast<Drawable>(entity);

	if (drawable) {

		auto animation = drawable->getAnimation();

		if (eventMessage == EntityEvent::COLLISION) {

			animation.frameNum = 0;
			animation.animName = AnimationName::COLLIDING;
		}
		else if (eventMessage == EntityEvent::INTERACTION) {

			if (entity->getState() == State::EVOLVING) {

				animation.animName = AnimationName::EVOLVING;
			}
			else {
				animation.animName = AnimationName::INTERACTING;
			}
				animation.frameNum = 0;
				entity->setInteractive(false);
				entity->setState(State::IDLE);
		}
		else if (eventMessage == EntityEvent::MOVE_LEFT) {

			if (animation.animName != AnimationName::RUNNING) {

				animation.animName = AnimationName::RUNNING;
				animation.frameNum = 0;
			}
		}
		else if (eventMessage == EntityEvent::IDLE) {
			animation.animName = AnimationName::IDLE;
		}
	}
}