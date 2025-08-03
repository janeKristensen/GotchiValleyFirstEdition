#pragma once
#include "SFML/Graphics.hpp"
#include "Components.h"


namespace GotchiValley {

	class Collidable {
	public:
		Collidable(const Transform& transform) { mCollider = Collider({ sf::FloatRect({transform.position.x , transform.position.y  }, { TILE_SIZE.x , TILE_SIZE.y  }) }); };
		virtual void update() = 0;
		Collider& getCollider() { return mCollider; };

	protected:
		Collider mCollider;
	};

	class Drawable {
	public:
		Drawable(Animation& animation, std::shared_ptr<sf::Texture> texture) : mAnimation(animation), mTexture(texture) {};
		virtual void initialize() = 0;
		void setSprite(sf::Sprite& sprite);
		sf::Sprite& getSprite() { return mSprite; };
		Animation& getAnimation() { return mAnimation; };
		void setAnimation(Animation& animation) { mAnimation = animation; };
		void setAnimationName(const AnimationName& name) { mAnimation.animName = name; };

	protected:
		std::shared_ptr<sf::Texture> mTexture = nullptr;
		sf::Sprite mSprite = sf::Sprite{ *mTexture };
		Animation& mAnimation;
	};
}
