#include "Creature.h"

using namespace GotchiValley;



	
//void Creature::setAnimation(Animation& animation){
//
//	mAnimation = animation;
//}
//Animation Creature::getAnimation(){}
//
//void Creature::setSprite(Sprite& sprite) {
//
//	mSprite = sprite;
//}
//
//
//Sprite& Creature::getSprite() {
//
//	return mSprite;
//}

Collider Creature::getCollider(){

	return mCollider;
}


std::shared_ptr<FollowBehaviour> Creature::getFollowBehaviour(){

	return mFollowBehaviour;
}

void Creature::setFollowBehaviour(std::shared_ptr<FollowBehaviour>& behaviour) {

	mFollowBehaviour = behaviour;
}

RoamBehaviour Creature::getRoamBehaviour(){

	return mRoamBehaviour;
}

void Creature::setRoamBehaviour(RoamBehaviour& behaviour) {

	mRoamBehaviour = behaviour;
}

void Creature::onClick(){

	std::cout << "Creature clicked" << std::endl;
}

