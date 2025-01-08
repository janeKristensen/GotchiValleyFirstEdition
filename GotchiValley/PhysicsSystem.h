#pragma once
#include "Entity.h"
#include "EntityManager.h"
#include "IObserver.h"
#include "SFML/Graphics.hpp"

enum DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class PhysicsSystem : public IObserver{
public:
	PhysicsSystem(ISubject& subject);
	void RemoveFromSubject();
	void OnNotify(EntityManager& manager, const sf::Event& event);
	void Update(EntityManager& manager, float dt);
	void RotateEntity(std::shared_ptr<Entity> entity, float rotation);
	void MoveEntity(std::shared_ptr<Entity> entity, DIRECTION direction);
	
private:
	ISubject& mSubject;
};