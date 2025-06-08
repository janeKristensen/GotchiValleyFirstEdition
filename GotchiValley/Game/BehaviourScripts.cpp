#include "BehaviourScripts.h"
#include "SharedObjects.h"
#include "Components.h"


using namespace GotchiValley;


void Behaviours::CreatureBehaviour(Entity entity) {

	auto entityFollow = componentRegistry.GetComponentOfType<FollowBehaviour>(entity);
	auto entityRoam = componentRegistry.GetComponentOfType<RoamBehaviour>(entity);

	if (entityFollow->isFollowActive) {

		entityFollow->isFollowActive = false;
		entityRoam->isRoamActive = true;
	}
	else {
		entityFollow->isFollowActive = true;
		entityRoam->isRoamActive = false;
	}
}

void Behaviours::EggBehaviour(Entity entity, const Animation& newAnimation) {

	auto evolutionState = componentRegistry.GetComponentOfType<EvolutionState>(entity);
	auto entityState = componentRegistry.GetComponentOfType<EntityState>(entity);
	auto entityAnimation = componentRegistry.GetComponentOfType<Animation>(entity);
	auto entityRoam = componentRegistry.GetComponentOfType<RoamBehaviour>(entity);
	auto entityButton = componentRegistry.GetComponentOfType<Button>(entity);

	if (evolutionState && evolutionState->state == State::UNEVOLVED) {

		entityState->state = State::EVOLVING;
		evolutionState->state = State::EVOLVED;
		entityRoam->isRoamActive = true;
		componentRegistry.RemoveComponent<Animation>(entity);
		componentRegistry.AddComponent<Animation>(entity, newAnimation);
	}

	entityButton->OnClick = [entity]() {
	
		Behaviours::CreatureBehaviour(entity);
	};
}

