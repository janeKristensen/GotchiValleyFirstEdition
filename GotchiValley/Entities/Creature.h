#pragma once
#include "Components.h"
#include "Entity.h"
#include "Interfaces.h"
#include "nlohmann/json.hpp"


namespace GotchiValley {

	class Creature : public Entity, public Collidable, public Drawable{

	public:
		Creature(
			const uint32_t& id,
			Transform transform,
			Animation& animation,
			std::shared_ptr<sf::Texture> texture,
			std::shared_ptr<FollowBehaviour>& followBehaviour,
			/*const RoamBehaviour& roamBehaviour,*/
			CreaturePhase phase = CreaturePhase::UNEVOLVED,
			bool interactable = false,
			bool moveable = false)
			: Entity(id, transform, interactable, moveable), Drawable(animation, texture), Collidable(transform)
		{
			mFollowBehaviour = followBehaviour;
			mCreaturePhase = phase;
			/*mRoamBehaviour = roamBehaviour;*/
		};

		std::shared_ptr<FollowBehaviour> getFollowBehaviour();
		void setFollowBehaviour(std::shared_ptr<FollowBehaviour> behaviour);
		void setFollowPath(std::vector<std::shared_ptr<Node>> newPath);
		void setPhase(CreaturePhase phase);
		CreaturePhase getPhase();
		/*void setRoamBehaviour(RoamBehaviour& behaviour);*/
		/*RoamBehaviour getRoamBehaviour();*/
		void onClick() override;
		void initialize() override;
		void update() override;

	private:
		std::shared_ptr<FollowBehaviour> mFollowBehaviour;
		CreaturePhase mCreaturePhase = CreaturePhase::UNEVOLVED;
		/*RoamBehaviour mRoamBehaviour;*/
			
	};
}

