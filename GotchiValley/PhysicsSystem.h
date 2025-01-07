#pragma once
#include "Entity.h"
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
	void OnNotify(Entity& entity, const sf::Event& event);
	void Update(Entity& entity, float dt);
	void RotateEntity(Entity& entity, float rotation);
	void MoveEntity(Entity& entity, DIRECTION direction);
	void StopEntityMovement(Entity& entity);
	
private:
	ISubject& mSubject;
	
};