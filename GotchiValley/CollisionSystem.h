#pragma once
#include "ComponentManager.h"
#include "Components.h"

namespace GotchiValley{

	class CollisionSystem {
	public:
		void Update(ComponentManager<Transform>& transformManager, ComponentManager<Collider>& colliderManager, ComponentManager<Moveable>& movementManager);
	private:
	};
}
