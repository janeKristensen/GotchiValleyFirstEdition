#pragma once
#include "Components.h"
#include "ComponentManager.h"

namespace GotchiValley {

	class MovementSystem {
	public:
		void Update(ComponentManager<Transform>& transformManager, ComponentManager<Controlable>& controlManager);
	private:

	};
}
