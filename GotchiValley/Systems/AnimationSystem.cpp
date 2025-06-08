#include "AnimationSystem.h"

using namespace GotchiValley;


void AnimationSystem::Update(float dt) {

	auto animArray = componentRegistry.GetComponentArray<Animation>();

	for (auto i = animArray.begin(); i != animArray.end(); i++) {

		auto animation = i->second;
		auto spriteComponent = componentRegistry.GetComponentOfType<Sprite>(i->first);
		auto entityState = componentRegistry.GetComponentOfType<EntityState>(i->first);
		
		animation->frameTime += dt;

		if (animation->frameTime > (1 / animation->frames[animation->animName].animFPS)) {

			animation->frameNum += std::uint8_t(animation->frameTime * animation->frames[animation->animName].animFPS);

			if (animation->frameNum >= animation->frames[animation->animName].numFrames) {

				animation->animName = AnimationName::IDLE;
				animation->frameNum = animation->frameNum % animation->frames[animation->animName].numFrames;
			}
		}
		
		uint8_t imageNum = animation->startFrame + animation->frameNum;
		spriteComponent->sprite.setTextureRect(animation->frames[animation->animName].sprites[imageNum]);
		animation->frameTime = fmod(animation->frameTime, (1 / animation->frames[animation->animName].animFPS));
	}	
}


void AnimationSystem::OnNotify(const Entity& entity, const EntityEvent& eventMessage) {

	auto animation = componentRegistry.GetComponentOfType<Animation>(entity);

	if (animation) {

		if (eventMessage == EntityEvent::COLLISION) {

			animation->frameNum = 0;
			animation->animName = AnimationName::COLLIDING;
		}
		else if (eventMessage == EntityEvent::INTERACTION) {

			auto entityState = componentRegistry.GetComponentOfType<EntityState>(entity);
			auto entityInteractable = componentRegistry.GetComponentOfType<Interactable>(entity);

			if (entityState && entityState->state == State::EVOLVING) {

				animation->animName = AnimationName::EVOLVING;
			}
			else {
				animation->animName = AnimationName::INTERACTING;
			}
				animation->frameNum = 0;
				entityInteractable->interactionActive = false;	
				entityState->state = State::IDLE;
		}
		else if (eventMessage == EntityEvent::MOVE_LEFT) {

			if (animation->animName != AnimationName::RUNNING) {

				animation->animName = AnimationName::RUNNING;
				animation->frameNum = 0;
			}
		}
		else if (eventMessage == EntityEvent::IDLE) {
			animation->animName = AnimationName::IDLE;
		}
	}
}