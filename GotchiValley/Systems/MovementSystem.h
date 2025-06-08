#pragma once
#include <unordered_set>
#include "IObserver.h"
#include "SharedObjects.h"
#include "GlobalVariables.h"
#include "Components.h"
#include "SFML/Graphics.hpp"
#include "Pathfinder.h"

namespace GotchiValley {

	class MovementSystem : public IGameSubject {
	public:
		~MovementSystem() {};
		void Update(float& dt);
		void AddObserver(IGameObserver* observer) override;
		void RemoveObserver(IGameObserver* observer) override;
		void NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const override;
	private:
		std::unordered_set<IGameObserver*> mObservers;
		const float mAcceleration = 1.f;
		void SetFollowPath(const std::unordered_map<Entity, std::shared_ptr<FollowBehaviour>>& followArray);
		void SetRoamPath(const std::unordered_map<Entity, std::shared_ptr<RoamBehaviour>>& roamArray);
		void FollowToNode(const std::unordered_map<Entity, std::shared_ptr<FollowBehaviour>>& followArray, const float& dt);
		void RoamToNode(const std::unordered_map<Entity, std::shared_ptr<RoamBehaviour>>& roamArray, const float& dt);
	};
}
