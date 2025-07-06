#pragma once
#include "Components.h"
#include "Entity.h"
#include "Interfaces.h"


namespace GotchiValley {

	class Creature : public Entity, public Collidable, public Drawable{

	public:
		Creature(
			const uint32_t& id,
			Transform& transform,
			Sprite& sprite,
			Animation& animation,
			std::shared_ptr<FollowBehaviour>& followBehaviour,
			RoamBehaviour& roamBehaviour,
			bool interactable = false,
			bool moveable = false)
			: Entity(id, transform, interactable, moveable), Drawable(sprite, animation)
		{
			//mSprite = sprite;
			mFollowBehaviour = followBehaviour;
			mRoamBehaviour = roamBehaviour;
			mCollider = Collider({ sf::FloatRect({transform.position.x , transform.position.y  }, { TILE_SIZE.x , TILE_SIZE.y  }) });
		};

		/*void setAnimation(Animation& animation);*/
		//Animation getAnimation() override;
	/*	void setSprite(Sprite& sprite) override;
		Sprite& getSprite() override;*/
		Collider getCollider() override;
		std::shared_ptr<FollowBehaviour> getFollowBehaviour();
		void setFollowBehaviour(std::shared_ptr<FollowBehaviour>& behaviour);
		void setRoamBehaviour(RoamBehaviour& behaviour);
		RoamBehaviour getRoamBehaviour();
		void onClick() override;


	private:

		/*Animation mAnimation;*/
		/*Sprite mSprite;*/
		Collider mCollider;
		std::shared_ptr<FollowBehaviour> mFollowBehaviour;
		RoamBehaviour mRoamBehaviour;
			
	};
}

