#pragma once
#include "GlobalVariables.h"
#include "SharedObjects.h"
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
		LevelManager(sf::Texture spritesheet);
		Level LoadLevel(std::uint32_t id);

	private:
		using Matrix = std::array<std::array<std::int32_t, LEVEL_SIZE.x>, LEVEL_SIZE.y>;
		std::uint32_t mLevelID = 0;
		sf::Texture mSpriteSheet;
		std::map<std::uint32_t, Matrix> mLevels;
		void LoadLevelFiles(std::filesystem::path filename);
	};

}
