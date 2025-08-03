
#include "PhysicsSystem.h"
#include "GameWorld.h"

using namespace GotchiValley;


void PhysicsSystem::update(float& dt) {

	std::array<std::shared_ptr<Entity>, MAX_ENTITIES>& entityArray = mGameWorld.getEntities();

	for (int i = 0; i < entityArray.size(); i++) {

		if (entityArray[i] == nullptr) break;

		if (entityArray[i] && entityArray[i]->isEntityAlive()) {

			Transform& transform = entityArray[i]->getTransform();
			transform.position += transform.velocity * dt * transform.speed;
			entityArray[i]->setTransform(transform);
			entityArray[i]->update();
			
			auto collider = std::dynamic_pointer_cast<Collidable>(entityArray[i]);
			if (!collider) continue;
			collider->getCollider().boundingBox.position = transform.position;

			transform.velocity = .95f * transform.velocity;
			entityArray[i]->setTransform(transform);
		}	
	}
}

void PhysicsSystem::onNotify(std::shared_ptr<Entity>& entity, const EntityEvent& eventMessage) {

	if (eventMessage == EntityEvent::COLLISION &&
		entity->isEntityAlive()) {
		
		
		Transform& transform = entity->getTransform();
		transform.velocity *= -1.f;
		entity->setTransform(transform);
		entity->update();
	}
}














