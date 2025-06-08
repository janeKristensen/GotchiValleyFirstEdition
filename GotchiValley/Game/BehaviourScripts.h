#pragma once
#include "GlobalVariables.h"
#include "Animations.h"

namespace GotchiValley{

	static class Behaviours {
	public:
		static void CreatureBehaviour(Entity entity);
		static void EggBehaviour(Entity entity, const Animation& newAnimation);
	};
	
}
