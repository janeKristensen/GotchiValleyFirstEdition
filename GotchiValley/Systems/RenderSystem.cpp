
#include "RenderSystem.h"


using namespace GotchiValley;


void RenderSystem::update(sf::RenderWindow& window) {

	std::shared_ptr<Level> level = mGameWorld.getCurrentLevel();
	auto entityArray = mGameWorld.getEntities();
	
	// Draw bounding boxes for the colliders of the level objects
#ifndef NDEBUG
	for (auto i = level->colliders.begin(); i != level->colliders.end(); i++) {

		sf::RectangleShape box{ {(float)TILE_SIZE.x, (float)TILE_SIZE.y} };
		box.setPosition(i->get()->boundingBox.position);
		window.draw(box);
	}
#endif

	sf::RenderStates states;
	states.texture = level->texture.get();
	window.draw(level->vertices, states);	
	
	for (auto i = 0; i < entityArray.size(); i++) {
	
		if (entityArray[i] && entityArray[i]->isEntityAlive()) {

			auto drawable = std::dynamic_pointer_cast<Drawable>(entityArray[i]);
			if (drawable) {

				window.draw(drawable->getSprite().sprite);
			}
			

#ifndef NDEBUG

			// Draws the bounding boxes for the game objects
			auto obj = std::dynamic_pointer_cast<Collidable>(entityArray[i]);
			if (obj) {
				auto collider = obj->getCollider();
				sf::RectangleShape box{ {(float)TILE_SIZE.x, (float)TILE_SIZE.y} };
				box.setPosition(collider.boundingBox.position);
				window.draw(box);
			}

			// Draws pathfinder paths
			auto creature = std::dynamic_pointer_cast<Creature>(entityArray[i]);
			if (creature) {

				std::shared_ptr<FollowBehaviour> followBehaviour = creature->getFollowBehaviour();
				for (const std::shared_ptr<Node>& node : followBehaviour->path) {

					sf::CircleShape nodeShape{ 5.f };
					sf::Vector2f position = { (float)node->x * TILE_SIZE.x, (float)node->y * TILE_SIZE.y };
					nodeShape.setPosition(position);
					nodeShape.setFillColor(sf::Color::Red);
					window.draw(nodeShape);
				}

				const RoamBehaviour& roamBehaviour = creature->getRoamBehaviour();
				for (const std::shared_ptr<Node>& node : roamBehaviour.path) {

					sf::CircleShape nodeShape{ 5.f };
					sf::Vector2f position = { (float)node->x * TILE_SIZE.x, (float)node->y * TILE_SIZE.y };
					nodeShape.setPosition(position);
					nodeShape.setFillColor(sf::Color::Blue);
					window.draw(nodeShape);
				}
			}
		}
	}
#endif


}

void RenderSystem::attachTexture(std::shared_ptr<Entity>& entity, const std::string& filename) {

	auto texture = std::make_unique<sf::Texture>();
	
	if (!texture->loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
	auto drawable = std::dynamic_pointer_cast<Drawable>(entity);
	if (drawable) {

		drawable->getSprite().texture = std::move(texture);
	}
}



