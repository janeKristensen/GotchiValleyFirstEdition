
#include "RenderSystem.h"


using namespace GotchiValley;


void RenderSystem::Update(sf::RenderWindow& window) {

	auto levelVertexArray = componentRegistry.GetComponentArray<Level>();
	for (auto i = levelVertexArray.begin(); i != levelVertexArray.end(); i++) {

		// Draw bounding boxes for the colliders of the level objects
#ifndef NDEBUG
		for (auto j = i->second->colliders.begin(); j != i->second->colliders.end(); j++) {

			Collider* collider = j->get();
			sf::RectangleShape box{ {(float)TILE_SIZE.x, (float)TILE_SIZE.y} };
			box.setPosition(collider->boundingBox.position);
			window.draw(box);
		}
#endif
		sf::RenderStates states;
		states.texture = i->second->texture.get();
		window.draw(i->second->vertices, states);	
	}

	// Draws the bounding boxes for the game objects
#ifndef NDEBUG
	auto colliderArray = componentRegistry.GetComponentArray<Collider>();
	for (auto i = colliderArray.begin(); i != colliderArray.end(); i++) {

		sf::RectangleShape box{ {(float)TILE_SIZE.x, (float)TILE_SIZE.y} };
		box.setPosition(i->second->boundingBox.position);
		window.draw(box);
	}
#endif

	// Draw pathfinder paths
#ifndef NDEBUG
	auto followArray = componentRegistry.GetComponentArray<FollowBehaviour>();
	for (auto i = followArray.begin(); i != followArray.end(); i++) {

		for (const std::shared_ptr<Node>& node : i->second->path) {

			sf::CircleShape nodeShape{5.f};
			sf::Vector2f position = { (float)node->x * TILE_SIZE.x, (float)node->y * TILE_SIZE.y};
			nodeShape.setPosition(position);
			nodeShape.setFillColor(sf::Color::Red);
			window.draw(nodeShape);
		}
	}

	auto roamArray = componentRegistry.GetComponentArray<RoamBehaviour>();
	for (auto i = roamArray.begin(); i != roamArray.end(); i++) {

		for (const std::shared_ptr<Node>& node : i->second->path) {

			sf::CircleShape nodeShape{ 5.f };
			sf::Vector2f position = { (float)node->x * TILE_SIZE.x, (float)node->y * TILE_SIZE.y };
			nodeShape.setPosition(position);
			nodeShape.setFillColor(sf::Color::Blue);
			window.draw(nodeShape);
		}
	}
#endif


	auto spriteArray = componentRegistry.GetComponentArray<Sprite>();
	for (auto i = spriteArray.begin(); i != spriteArray.end(); i++) {

		window.draw(i->second->sprite);
	}
}

void RenderSystem::AttachTexture(Entity& entity, const std::string& filename) {

	auto spriteComponent = componentRegistry.GetComponentOfType<Sprite>(entity);
	auto texture = std::make_unique<sf::Texture>();
	
	if (!texture->loadFromFile(std::filesystem::absolute(filename).string()))
	{
		throw std::runtime_error("Could not load image.png");
	}
	spriteComponent->sprite.setTexture(*texture);
	spriteComponent->texture = std::move(texture);
}

//sf::Texture& RenderSystem::LoadTexture(const std::string& filename) {
//
//	sf::Texture texture;
//	if (!texture.loadFromFile(std::filesystem::absolute(filename).string()))
//	{
//		throw std::runtime_error("Could not load image.png");
//	}
//	return texture;
//}

