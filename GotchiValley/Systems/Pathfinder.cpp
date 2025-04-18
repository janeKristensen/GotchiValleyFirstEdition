#include "Pathfinder.h"

/* Implementation stolen from https://dev.to/jansonsa/a-star-a-path-finding-c-4a4h*/

using namespace GotchiValley;

inline bool operator < (const Node& lhs, const Node& rhs)
{
	return lhs.fCost < rhs.fCost;
}

bool Pathfinder::IsValid(uint32_t x, uint32_t y) {

	if (x < 0 || y < 0 ||
		x >= SCREEN_SIZE.x / TILE_SIZE.x ||
		y >= SCREEN_SIZE.y / TILE_SIZE.y ) {
		return false;
	}

	return true;
}

bool Pathfinder::IsDestination(uint32_t x, uint32_t y, Node dest) {

	return x == dest.x && y == dest.y;
}


double Pathfinder::CalculateH(uint32_t x, uint32_t y, Node dest) {
	double H = (sqrt((x - dest.x) * (x - dest.x)
		+ (y - dest.y) * (y - dest.y)));
	return H;
}

std::vector<Node> Pathfinder::MakePath(std::array<std::array<Node, (SCREEN_SIZE.y / TILE_SIZE.y)>, (SCREEN_SIZE.x / TILE_SIZE.x)>& map, Node& dest) {

	try {
		std::cout << "Found a path.";

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

		path.push(map[x][y]);

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

	if (!IsValid(dest.x, dest.y)) {

		std::cout << "Invalid destionation for pathfinding.";
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
		}
	}

	uint32_t x = actor.x;
	uint32_t y = actor.y;
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList{allMap[x][y]};
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < (SCREEN_SIZE.x / TILE_SIZE.x * SCREEN_SIZE.y / TILE_SIZE.y)) {

		Node node;

		do {
			float temp = FLT_MAX;
			std::vector<Node>::iterator itNode;
			for (auto it = openList.begin(); it != openList.end(); it++) {

				if (it->fCost < temp) {
					temp = it->fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!IsValid(node.x, node.y));

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (auto newX = -1; newX <= 1; newX++) {
			for (auto newY = -1; newY <= 1; newY++) {
				double gNew, fNew, hNew;
				if (IsValid(x + newX, y + newY)) {
					if (IsDestination(x + newX, y + newY, dest)) {

						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;

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
	}
	if (!destinationFound) {

		std::cout << "Destination was not found.";
		return empty;
	}
}


