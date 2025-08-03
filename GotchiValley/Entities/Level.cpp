#include "Level.h"

using namespace GotchiValley;

void Level::update() {

}

std::vector<std::shared_ptr<Collider>>& Level::getColliderArray() {

	return mColliders;
}

std::shared_ptr<sf::Texture> Level::getTexture() {

	return mTexture;
}

sf::VertexArray Level::getVertices() {

	return mVertices;
}