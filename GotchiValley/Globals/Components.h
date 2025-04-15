#pragma once
#include "GlobalVariables.h"
#include "SFML/Graphics.hpp"
#include <cstdint>

namespace GotchiValley {

	struct PlayerStats {
		std::uint16_t health;
	};

	struct EntityState {
		State state	= State::IDLE;
	};

	struct Transform {
		sf::Vector2f position;
		sf::Vector2f velocity;
		float speed	= 0.f;
	};

	struct Controlable {
		bool controlable = true;
	};

	struct Collider {
		sf::FloatRect boundingBox;
		bool hasCollided = false;
	};

	struct Moveable {};

	struct Sprite {
		std::shared_ptr<sf::Texture> texture;
		sf::Sprite sprite = sf::Sprite(*texture);
		size_t drawOrder = 0;
	};

	struct AnimationData {
		uint8_t numFrames = 1;
		std::vector<sf::IntRect> sprites;
		float animFPS = 24.0f;
	};

	struct Animation {
		std::unordered_map<AnimationName, AnimationData> frames;
		uint8_t startFrame = 0;
		uint8_t frameNum = 0;
		float frameTime	= 0.f;
		AnimationName animName = AnimationName::IDLE;
	};

	struct Interactable {
		bool interactionActive = false;
	};

	struct Level {
		sf::VertexArray vertices;
		sf::Texture texture;
		std::vector<Collider> colliders;
	};
}




