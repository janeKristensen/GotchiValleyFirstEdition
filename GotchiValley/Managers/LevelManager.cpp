#include "LevelManager.h"

using namespace GotchiValley;

LevelManager::LevelManager(sf::Texture spritesheet) {

	mSpriteSheet = spritesheet;
	std::string filepath = "D:\\Visual Studio stuff\\Projekts\\Games\\GotchiValley\\resources\\levels";
	for (auto const& file : std::filesystem::directory_iterator(filepath)) {
		LoadLevelFiles(file.path());
	}
}

Level LevelManager::LoadLevel(std::uint32_t id) {

	Matrix level = mLevels.at(id);
	sf::VertexArray vertices(sf::PrimitiveType::Triangles);
	vertices.resize(LEVEL_SIZE.x * LEVEL_SIZE.y * 6);


	for (std::int32_t i = 0; i < LEVEL_SIZE.x; i++) {
		for (std::int32_t j = 0; j < LEVEL_SIZE.y; j++)
		{
			// get the current tile number
			//const std::uint32_t tileNumber = level[i + j * LEVEL_SIZE.x];
			const std::uint32_t tileNumber = level[i][j];

			// find its position in the tileset texture
			const int tu = tileNumber % (TILE_SET_SIZE.x * TILE_SIZE.x / TILE_SIZE.x);
			const int tv = tileNumber / (TILE_SET_SIZE.x * TILE_SIZE.x / TILE_SIZE.x);

			// get a pointer to the triangles' vertices of the current tile
			sf::Vertex* triangles = &vertices[(i + j * LEVEL_SIZE.x) * 6];

			// define the 6 corners of the two triangles
			triangles[0].position = sf::Vector2f(j * TILE_SIZE.x, i * TILE_SIZE.y);
			triangles[1].position = sf::Vector2f((j + 1) * TILE_SIZE.x, i * TILE_SIZE.y);
			triangles[2].position = sf::Vector2f(j * TILE_SIZE.x, (i + 1) * TILE_SIZE.y);
			triangles[3].position = sf::Vector2f(j * TILE_SIZE.x, (i + 1) * TILE_SIZE.y);
			triangles[4].position = sf::Vector2f((j + 1) * TILE_SIZE.x, i * TILE_SIZE.y);
			triangles[5].position = sf::Vector2f((j + 1) * TILE_SIZE.x, (i + 1) * TILE_SIZE.y);

			// define the 6 matching texture coordinates
			triangles[0].texCoords = sf::Vector2f(tu * TILE_SIZE.x, tv * TILE_SIZE.y);
			triangles[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE.x, tv * TILE_SIZE.y);
			triangles[2].texCoords = sf::Vector2f(tu * TILE_SIZE.x, (tv + 1) * TILE_SIZE.y);
			triangles[3].texCoords = sf::Vector2f(tu * TILE_SIZE.x, (tv + 1) * TILE_SIZE.y);
			triangles[4].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE.x, tv * TILE_SIZE.y);
			triangles[5].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE.x, (tv + 1) * TILE_SIZE.y);
		
		}
	}

	Level levelMap{ vertices, mSpriteSheet };
	return levelMap;
}

void LevelManager::LoadLevelFiles(std::filesystem::path filename){

	Matrix level{};
	std::fstream levelFile(filename);

	for (std::int32_t i = 0; i < LEVEL_SIZE.x; i++) {
		for (std::int32_t j = 0; j < LEVEL_SIZE.x; j++) {
			
			char number;
			levelFile >> number;
			if (number == 10)
				continue;

			level[i][j] = number - '0';
		}
	}

	levelFile.close();

	mLevels[mLevelID] = level;
	mLevelID++;
}

