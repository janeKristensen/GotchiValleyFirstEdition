#include "AnimationSystem.h"

using namespace GotchiValley;

void AnimationSystem::Update(float dt) {

	
	auto animArray = componentRegistry.GetComponentArray<Animation>();

	for (auto i = animArray.begin(); i != animArray.end(); i++) {

		auto animation = i->second;
		animation->frameTime += dt;

		if (animation->frameTime > (1 / animation->frames[animation->animNum].animFPS)) {

			animation->frameNum += std::uint8_t(animation->frameTime * animation->frames[animation->animNum].animFPS);

			if (animation->frameNum >= animation->frames[animation->animNum].numFrames) {
				
				animation->frameNum = animation->frameNum % animation->frames[animation->animNum].numFrames;
			}

			uint8_t imageNum = animation->startFrame + animation->frameNum;
			auto spriteComponent = componentRegistry.GetComponentOfType<Sprite>(i->first);
			spriteComponent->sprite.setTextureRect(animation->frames[animation->animNum].sprites[imageNum]);

			animation->frameTime = fmod(animation->frameTime, (1 / animation->frames[animation->animNum].animFPS));
		}
	}	
}