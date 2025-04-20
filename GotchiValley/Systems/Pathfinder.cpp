#include "Pathfinder.h"

/* Implementation stolen from https://dev.to/jansonsa/a-star-a-path-finding-c-4a4h*/

using namespace GotchiValley;


//
//bool Pathfinder::IsValid(int32_t x, int32_t y) {
//
//	int32_t count = GameWorld::Get().GetColliderCount(x, y);
//	if (count == 0)
//	{
//		return true;
//	}
//
//	return false;
//}

bool Pathfinder::IsDestination(int32_t x, int32_t y, Node dest) {

	return x == dest.x && y == dest.y;
}

bool Pathfinder::IsValid(int32_t x, int32_t y) {

	if (x < 0 || y < 0 ||
		x >= SCREEN_SIZE.x / TILE_SIZE.x ||
		y >= SCREEN_SIZE.y / TILE_SIZE.y ||
		GameWorld::Get().GetColliderCount(x, y) != 0) {
		return false;
	}
}


double Pathfinder::CalculateH(int32_t x, int32_t y, Node dest) {
	double H = (sqrt((x - dest.x) * (x - dest.x)
		+ (y - dest.y) * (y - dest.y)));
	return H;
}

std::vector<Node> Pathfinder::MakePath(std::array<std::array<Node, (SCREEN_SIZE.y / TILE_SIZE.y)>, (SCREEN_SIZE.x / TILE_SIZE.x)>& map, Node& dest) {

	try {
		auto x = dest.x;
		auto y = dest.y;
		std::stack<Node> path;
		std::vector<Node> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y) &&
			map[x][y].x != -1 && map[x][y].y != -1) {

			path.push(map[x][y]);
			auto tempX = map[x][y].parentX;
			auto tempY = map[x][y].parentY;
			x = tempX; 
			y = tempY;
		}

		//path.push(map[x][y]);

		while (!path.empty()) {

			Node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}

		return usablePath;

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

std::vector<Node> Pathfinder::FindPath(Node actor, Node dest) {

	std::vector<Node> empty;

	if (dest.x < 0 || dest.y < 0 ||
		dest.x >= SCREEN_SIZE.x / TILE_SIZE.x ||
		dest.y >= SCREEN_SIZE.y / TILE_SIZE.y) {

		std::cout << "Invalid destination for pathfinding.";
		return empty;
	}
	if (IsDestination(actor.x, actor.y, dest)) {

		std::cout << "Destination of path is the same as origin.";
		return empty;
	}

	bool closedList[SCREEN_SIZE.x / TILE_SIZE.x][SCREEN_SIZE.y / TILE_SIZE.y];

	std::array<std::array<Node, (SCREEN_SIZE.y / TILE_SIZE.y)>, (SCREEN_SIZE.x / TILE_SIZE.x)> allMap;
	for (auto x = 0; x < (SCREEN_SIZE.x / TILE_SIZE.x); x++) {
		for (auto y = 0; y < (SCREEN_SIZE.y / TILE_SIZE.y); y++) {

			allMap[x][y].fCost = FLT_MAX;
			allMap[x][y].gCost = FLT_MAX;
			allMap[x][y].hCost = FLT_MAX;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;
			
			// Skip inflation if it's the start or target tile
			if ((x == actor.x && y == actor.y) || (x == dest.x && y == dest.y))
				continue;

			if (GameWorld::Get().GetColliderCount(x, y) != 0) {

				allMap[x][y].walkable = false;
			}
		}
	}

	int32_t x = actor.x;
	int32_t y = actor.y;
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;


	//std::vector<Node> openList;
	std::list<Node> openList;
	openList.emplace_back(allMap[x][y]);

	while (!openList.empty() && openList.size() < (SCREEN_SIZE.x / TILE_SIZE.x * SCREEN_SIZE.y / TILE_SIZE.y)) {

		Node node;
		openList.sort([](const Node& lhs, const Node& rhs) {return lhs.fCost < rhs.fCost; });

		do {
			float temp = FLT_MAX;
			std::list<Node>::iterator itNode;
			for (std::list<Node>::iterator it = openList.begin(); it != openList.end(); it++) {
				Node n = *it;
				if (n.fCost < temp) {
					temp = n.fCost;
					itNode = it;
				}
			}
			
			node = *itNode;
			openList.erase(itNode);

		} while (!allMap[x][y].walkable);

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (auto newX = -1; newX <= 1; newX++) {
			for (auto newY = -1; newY <= 1; newY++) {
				double gNew, fNew, hNew;

				if (x <= 0 || y <= 0 ||
					x >= SCREEN_SIZE.x / TILE_SIZE.x ||
					y >= SCREEN_SIZE.y / TILE_SIZE.y) continue;

				if (IsDestination(x + newX, y + newY, dest)) {

					allMap[x + newX][y + newY].parentX = x;
					allMap[x + newX][y + newY].parentY = y;

					return MakePath(allMap, dest);
				}
				else if (closedList[x + newX][y + newY] == false) {

					gNew = node.gCost + 1.0f;
					hNew = CalculateH(x + newX, y + newY, dest);
					fNew = gNew + hNew;

					if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
						allMap[x + newX][y + newY].fCost > fNew) {

						allMap[x + newX][y + newY].fCost = fNew;
						allMap[x + newX][y + newY].gCost = gNew;
						allMap[x + newX][y + newY].hCost = hNew;
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						openList.emplace_back(allMap[x + newX][y + newY]);
					}
				}
			}
		}
	}
	
	std::cout << "Destination was not found.";
	return empty;
}


