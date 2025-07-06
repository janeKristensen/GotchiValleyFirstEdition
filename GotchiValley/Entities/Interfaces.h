#pragma once
#include "Components.h"


namespace GotchiValley {

	class Collidable {
	public:
		virtual Collider getCollider() = 0;
	};

	class Drawable {
	public:
		Drawable(Sprite sprite, Animation animation) : mSprite(sprite), mAnimation(animation) {};
		void setSprite(Sprite& sprite);
		inline Sprite& getSprite() { return mSprite; };
		Animation getAnimation() { return mAnimation; };
	private:
		Sprite mSprite;
		Animation mAnimation;
	};
}
