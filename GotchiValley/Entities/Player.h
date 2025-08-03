#pragma once
#include "Components.h"
#include "Entity.h"
#include "Interfaces.h"

namespace GotchiValley {

	class Player : public Entity, public Drawable, public Collidable {

	public:
		Player(
			const uint32_t& id,
			Transform transform,
			Animation& animation,
			std::shared_ptr<sf::Texture> texture,
			bool interactable = false,
			bool moveable = false) : Entity(id, transform, interactable, moveable), Drawable(animation, texture), Collidable(transform) {
			setState(State::INITIAL);
		};
		void initialize() override;
		void update() override;

	private:
		
	};
}