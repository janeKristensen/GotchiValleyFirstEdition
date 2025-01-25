#pragma once
#include "SFML/Graphics.hpp"
#include <cstdint>

namespace GotchiValley {

	struct PlayerStats {
		std::uint16_t health;
	};

	struct Transform {
		sf::Vector2f position;
		sf::Vector2f velocity;
		float speed = 0.f;
	};

	struct Controlable {
		bool controlable = true;
	};

	struct Collider {
		sf::FloatRect boundingBox;
	};

	struct Moveable {};

	struct Sprite {
		std::shared_ptr<sf::Texture> texture;
		sf::Sprite sprite = sf::Sprite(*texture);
		size_t drawOrder = 0;
	};

	struct AnimationData {
		uint8_t numFrames;
		std::vector<sf::IntRect> sprites;
		float animFPS = 24.0f;
	};

	struct Animation {
		std::vector<AnimationData> frames;
		uint8_t startFrame = 0;
		uint8_t frameNum = 0;
		float frameTime = 0.f;
		uint8_t animNum = 0;
	};
}




