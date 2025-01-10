#pragma once
#include "Entity.h"
#include "EntityManager.h"
#include "IObserver.h"
#include "SFML/Graphics.hpp"



class PhysicsSystem : public IObserver{
public:
	PhysicsSystem(ISubject& subject);
	void RemoveFromSubject();
	void OnNotify(EntityManager& manager, const sf::Event& event, std::string message);
	void Update(EntityManager& manager, float dt);
	void RotateEntity(std::shared_ptr<Entity> entity, float rotation);
	void ResolveCollisions(EntityManager& manager);
private:
	ISubject& mSubject;
};