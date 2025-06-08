#pragma once
#include "GlobalVariables.h"
#include "Components.h"
#include "Factory.h"
#include "SFML/Graphics.hpp"
#include <map>
#include <array>
#include <iostream>
#include <fstream>

namespace GotchiValley {

	class LevelManager {

	public:
		
		LevelManager(std::shared_ptr<sf::Texture> spritesheet);
		Level LoadLevel(uint32_t id);
		uint32_t GetNumberOfLevels();


	private:
		using Matrix = std::array<std::array<uint32_t, LEVEL_SIZE.x>, LEVEL_SIZE.y>;
		uint32_t mLevelID = 1;
		std::shared_ptr<sf::Texture> mSpriteSheet;
		std::map<uint32_t, Matrix> mLevels;
		std::array<std::array<TileNode, (SCREEN_SIZE.y / TILE_SIZE.y)>, (SCREEN_SIZE.x / TILE_SIZE.x)> mColliderMap; 
		void LoadLevelFiles(std::filesystem::path filename);
	};

}
