#include "BehaviourScripts.h"
#include "SharedObjects.h"
#include "Components.h"
#include "Animations.h"

using namespace GotchiValley;

	void Behaviours::BirdBehaviour(Entity entity) {

		auto evolutionState = componentRegistry.GetComponentOfType<EvolutionState>(entity);
		auto entityState = componentRegistry.GetComponentOfType<EntityState>(entity);
		auto entityAnimation = componentRegistry.GetComponentOfType<Animation>(entity);
		auto entityFollow = componentRegistry.GetComponentOfType<FollowBehaviour>(entity);
		auto entityRoam = componentRegistry.GetComponentOfType<RoamBehaviour>(entity);

		if (evolutionState && evolutionState->state == State::UNEVOLVED) {

			entityState->state = State::EVOLVING;
			evolutionState->state = State::EVOLVED;
			entityRoam->isRoamActive = true;
			componentRegistry.RemoveComponent<Animation>(entity);
			componentRegistry.AddComponent<Animation>(entity, birdAnimation);
		}
		else if (evolutionState && evolutionState->state == State::EVOLVED) {

			if (entityFollow->isFollowActive) {

				entityFollow->isFollowActive = false;
				entityRoam->isRoamActive = true;
			}
			else {
				entityFollow->isFollowActive = true;
				entityRoam->isRoamActive = false;
			}
		};
	}
