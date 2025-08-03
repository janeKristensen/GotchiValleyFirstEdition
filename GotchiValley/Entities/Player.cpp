#include "Player.h"

using namespace GotchiValley;

void Player::initialize() {

	mSprite.setPosition(mTransform.position);
}

void Player::update() {

	mSprite.setPosition(mTransform.position);
	mCollider.boundingBox.position = mTransform.position;
}