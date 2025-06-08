#include "LevelManager.h"
#include "GlobalVariables.h"

using namespace GotchiValley;

LevelManager::LevelManager(std::shared_ptr<sf::Texture> spritesheet) {

	mSpriteSheet = spritesheet;
	std::string filepath = "D:\\Visual Studio stuff\\Projekts\\Games\\GotchiValley\\resources\\levels";
	for (auto const& file : std::filesystem::directory_iterator(filepath)) {
		LoadLevelFiles(file.path());
	}
}

Level LevelManager::LoadLevel(uint32_t id) {

	Matrix level = mLevels.at(id);
	std::vector<std::shared_ptr<Collider>> colliders;
	sf::VertexArray vertices(sf::PrimitiveType::Triangles);
	vertices.resize(LEVEL_SIZE.x * LEVEL_SIZE.y * 6);


	for (int32_t i = 0; i < LEVEL_SIZE.x; i++) {
		for (int32_t j = 0; j < LEVEL_SIZE.y; j++)
		{
			// get the current tile number
			const int32_t tileNumber = level[i][j];

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
		
			if (tileNumber % 2 != 0) {

				const sf::Vector2f& size = static_cast<sf::Vector2f>(TILE_SIZE);
				const sf::Vector2f& position = triangles[0].position;
				colliders.push_back(std::make_shared<Collider>(Collider{ sf::FloatRect(position, size) }));
			}
		}
	}

	for (auto x = 0; x < (SCREEN_SIZE.x / TILE_SIZE.x); x++) {
		for (auto y = 0; y < (SCREEN_SIZE.y / TILE_SIZE.y); y++) {

			mColliderMap[x][y].count = 0;
		}
	}

	for (auto i = colliders.begin(); i != colliders.end(); i++) {

		int32_t tempX = i->get()->boundingBox.position.x / TILE_SIZE.x;
		int32_t tempY = i->get()->boundingBox.position.y / TILE_SIZE.y;

		mColliderMap[tempX][tempY].count += 1;
		mColliderMap[tempX - 1][tempY].count += 1;
		mColliderMap[tempX + 1][tempY].count += 1;
		mColliderMap[tempX][tempY - 1].count += 1;
		mColliderMap[tempX][tempY + 1].count += 1;
		mColliderMap[tempX - 1][tempY - 1].count += 1;
		mColliderMap[tempX + 1][tempY + 1].count += 1;
		mColliderMap[tempX + 1][tempY - 1].count += 1;
		mColliderMap[tempX - 1][tempY + 1].count += 1;

	}
	
	for (auto x = 0; x < (SCREEN_SIZE.x / TILE_SIZE.x); x++) {
		for (auto y = 0; y < (SCREEN_SIZE.y / TILE_SIZE.y); y++) {

			allMap[x][y] = std::make_shared<Node>();

			allMap[x][y]->fCost = FLT_MAX;
			allMap[x][y]->gCost = FLT_MAX;
			allMap[x][y]->hCost = FLT_MAX;
			allMap[x][y]->parentX = -1;
			allMap[x][y]->parentY = -1;
			allMap[x][y]->x = x;
			allMap[x][y]->y = y;

			if (mColliderMap[x][y].count != 0) {
				allMap[x][y]->walkable = false;
				//std::cout << "tile x:" << allMap[x][y]->x << " y: " << allMap[x][y]->y << " not walkable" << std::endl;
			}
		}
	}

	Level levelMap{ id, vertices, mSpriteSheet, colliders };
	return levelMap;
}

void LevelManager::LoadLevelFiles(std::filesystem::path filename){

	Matrix level{};
	std::fstream levelFile(filename);

	for (int32_t i = 0; i < LEVEL_SIZE.x; i++) {
		for (int32_t j = 0; j < LEVEL_SIZE.x; j++) {
			
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

uint32_t LevelManager::GetNumberOfLevels() {

	return mLevelID;
}

