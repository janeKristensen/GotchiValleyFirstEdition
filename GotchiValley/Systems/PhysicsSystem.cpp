
#include "PhysicsSystem.h"

using namespace GotchiValley;


void PhysicsSystem::update(float& dt) {

	auto entityArray = mGameWorld.getEntities();

	for (int i = 0; i < entityArray.size(); i++) {

		if (entityArray[i] && entityArray[i]->isEntityAlive()) {

			Transform transform = entityArray[i]->getTransform();
			transform.position += transform.velocity * dt * transform.speed;

			setPosition(entityArray[i], transform.position);
			
			auto collider = std::dynamic_pointer_cast<Collidable>(entityArray[i]);
			if (!collider) continue;
			collider->getCollider().boundingBox.position = transform.position;

			transform.velocity = .95f * transform.velocity;
		}	
	}
}


void PhysicsSystem::setPosition(std::shared_ptr<Entity>& entity, sf::Vector2f& position) {

	Transform transform = entity->getTransform();
	transform.position = position;
	entity->setTransform(transform);
	
	auto drawable = std::dynamic_pointer_cast<Drawable>(entity);
	if (drawable) {

		Sprite& spriteComponent = drawable->getSprite();
		spriteComponent.sprite.setPosition(transform.position);
	}
}


void PhysicsSystem::onNotify(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) {

	if (eventMessage == EntityEvent::COLLISION &&
		entity->isEntityAlive()) {
		
		
		Transform transform = entity->getTransform();
		transform.velocity *= -1.f;
	}
}














