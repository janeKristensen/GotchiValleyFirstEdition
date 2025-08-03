#include "Creature.h"

using namespace GotchiValley;

void Creature::initialize() {

	mSprite.setPosition(mTransform.position);
}

void Creature::update() {

	mSprite.setPosition(mTransform.position);
	mCollider.boundingBox.position = mTransform.position;
}

std::shared_ptr<FollowBehaviour> Creature::getFollowBehaviour(){

	return mFollowBehaviour;
}

void Creature::setFollowBehaviour(std::shared_ptr<FollowBehaviour> behaviour) {

	mFollowBehaviour = behaviour;
}

void Creature::setFollowPath(std::vector<std::shared_ptr<Node>> newPath) {

	mFollowBehaviour->path = newPath;
	mFollowBehaviour->hasPath = true;
}

//RoamBehaviour Creature::getRoamBehaviour(){
//
//	return mRoamBehaviour;
//}
//
//void Creature::setRoamBehaviour(RoamBehaviour& behaviour) {
//
//	mRoamBehaviour = behaviour;
//}

void Creature::onClick(){

	std::cout << "Creature clicked" << std::endl;
	mFollowBehaviour->isFollowActive ? mFollowBehaviour->isFollowActive = false : mFollowBehaviour->isFollowActive = true;
}

