#pragma once
#include "GlobalVariables.h"
#include "SFML/Graphics.hpp"
#include <cstdint>
#include <functional>

namespace GotchiValley {

	struct Transform {
		sf::Vector2f position;
		sf::Vector2f velocity;
		float speed	= 0.f;
	};

	struct Collider {
		sf::FloatRect boundingBox;
		bool hasCollided = false;
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

	//struct RoamBehaviour {
	//	std::vector<std::shared_ptr<Node>> path;
	//	size_t currentStep = 0;
	//	bool hasPath = false;
	//	bool isRoamActive = false;
	//};

	class Entity;

	struct FollowBehaviour {
		std::shared_ptr<Entity> entity;
		std::vector<std::shared_ptr<Node>> path;
		size_t currentStep = 0;
		bool hasPath = false;
		bool isFollowActive = false;
	};
}




