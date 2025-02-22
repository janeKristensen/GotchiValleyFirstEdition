#include "AnimationSystem.h"

using namespace GotchiValley;


void AnimationSystem::Update(float dt) {

	auto animArray = componentRegistry.GetComponentArray<Animation>();

	for (auto i = animArray.begin(); i != animArray.end(); i++) {

		auto animation = i->second;
		auto spriteComponent = componentRegistry.GetComponentOfType<Sprite>(i->first);
		
		animation->frameTime += dt;

		if (animation->frameTime > (1 / animation->frames[animation->animName].animFPS)) {

			animation->frameNum += std::uint8_t(animation->frameTime * animation->frames[animation->animName].animFPS);

			if (animation->frameNum >= animation->frames[animation->animName].numFrames) {

				if (animation->animName == AnimationName::COLLIDING) {

					animation->animName = AnimationName::INITIAL;
					
				}
				else if (animation->animName == AnimationName::INTERACTING) {
					
					animation->animName = AnimationName::IDLE; 
				}
					
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

	if (eventMessage == EntityEvent::COLLISION) {

		animation->frameNum = 0;
		animation->animName = AnimationName::COLLIDING;
		
	}
	else if (eventMessage == EntityEvent::INTERACTION) {

		auto animArray = componentRegistry.GetComponentArray<Animation>();

		for (auto i = animArray.begin(); i != animArray.end(); i++) {
			auto interactable = componentRegistry.GetComponentOfType<Interactable>(i->first);
			if (!interactable) continue;
			
			else if (interactable->interactionActive) {

				i->second->frameNum = 0;
				i->second->animName = AnimationName::INTERACTING;
				interactable->interactionActive = false;
			}
				
			
		}
	}
	else if(eventMessage == EntityEvent::MOVE_RIGHT) {

		if (animation->animName != AnimationName::RUNNING) {

			animation->animName = AnimationName::RUNNING;
			animation->frameNum = 0;
		}
		
	}
	else if (eventMessage == EntityEvent::IDLE) {
		animation->animName = AnimationName::IDLE;
	}
}