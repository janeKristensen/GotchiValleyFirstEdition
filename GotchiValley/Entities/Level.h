#pragma once
#include "Components.h"

namespace GotchiValley{

	class Level {
	public:
		Level(uint32_t levelId) : mLevelId(levelId) {};
		Level(uint32_t levelId, sf::VertexArray vertices,
		std::shared_ptr<sf::Texture> texture,
		std::vector<std::shared_ptr<Collider>> colliders) {
			mLevelId = levelId;
			mVertices = vertices;
			mTexture = texture;
			mColliders = colliders;
		};

		Level(const Level& level) {
			mLevelId = level.mLevelId;
			mVertices = level.mVertices;
			mTexture = level.mTexture;
			mColliders = level.mColliders;
		};

		void update();
		std::vector<std::shared_ptr<Collider>>& getColliderArray();
		std::shared_ptr<sf::Texture> getTexture();
		sf::VertexArray getVertices();

	private:
		uint32_t mLevelId;
		sf::VertexArray mVertices;
		std::shared_ptr<sf::Texture> mTexture;
		std::vector<std::shared_ptr<Collider>> mColliders;
	};
}
