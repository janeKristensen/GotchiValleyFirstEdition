#include "Pathfinder.h"
#include "GlobalVariables.h"


/* Implementation stolen from https://dev.to/jansonsa/a-star-a-path-finding-c-4a4h
Modified to optimize memory usage*/

using namespace GotchiValley;


bool Pathfinder::IsDestination(const int32_t& x, const int32_t& y, const Node& dest) {

	return x == dest.x && y == dest.y;
}

double Pathfinder::CalculateH(const int32_t& x, const int32_t& y, const Node& dest) {
	double H = (sqrt((x - dest.x) * (x - dest.x)
		+ (y - dest.y) * (y - dest.y)));
	return H;
}

std::vector<std::shared_ptr<Node>> Pathfinder::MakePath(const Node& dest) {

	try {
		auto x = dest.x;
		auto y = dest.y;
		std::stack<std::shared_ptr<Node>> path;
		std::vector<std::shared_ptr<Node>> usablePath;

		while (!(allMap[x][y]->parentX == x && allMap[x][y]->parentY == y) &&
			allMap[x][y]->x != -1 && allMap[x][y]->y != -1) {

			path.push(allMap[x][y]);
			auto tempX = allMap[x][y]->parentX;
			auto tempY = allMap[x][y]->parentY;
			x = tempX; 
			y = tempY;
		}

		path.push(allMap[x][y]);

		while (!path.empty()) {

			usablePath.emplace_back(path.top());
			path.pop();
		}

		return usablePath;

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

std::vector<std::shared_ptr<Node>> Pathfinder::FindPath(const Node& actor, const Node& dest) {

	std::vector<std::shared_ptr<Node>> empty;

	/* Check that destination cell is within bounds and that it is not the same cell as origin*/
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

	/* Create and initialize a list of nodes to track which has already been visited. */
	bool closedList[SCREEN_SIZE.x / TILE_SIZE.x][SCREEN_SIZE.y / TILE_SIZE.y];

	/* Initilize the grid of map cells. */
	for (auto x = 0; x < (SCREEN_SIZE.x / TILE_SIZE.x); x++) {
		for (auto y = 0; y < (SCREEN_SIZE.y / TILE_SIZE.y); y++) {
			
			allMap[x][y]->fCost = FLT_MAX;
			allMap[x][y]->gCost = FLT_MAX;
			allMap[x][y]->hCost = FLT_MAX;
			allMap[x][y]->parentX = -1;
			allMap[x][y]->parentY = -1;
			allMap[x][y]->x = x;
			allMap[x][y]->y = y;
			closedList[x][y] = false;
		}
	}

	/* Initialize the starting node. */
	int32_t x = actor.x;
	int32_t y = actor.y;
	allMap[x][y]->fCost = 0.0;
	allMap[x][y]->gCost = 0.0;
	allMap[x][y]->hCost = 0.0;
	allMap[x][y]->parentX = x;
	allMap[x][y]->parentY = y;


	/* Create a list of nodes to test for walkability. 
		Loop through list until we find a node that can be traversed. */
	std::list<std::shared_ptr<Node>> openList;
	openList.emplace_back(allMap[x][y]);

	while (!openList.empty() && openList.size() < (SCREEN_SIZE.x / TILE_SIZE.x * SCREEN_SIZE.y / TILE_SIZE.y)) {

		std::shared_ptr<Node> node;
		openList.sort([](const std::shared_ptr<Node> lhs, const std::shared_ptr<Node> rhs) {return lhs->fCost < rhs->fCost; });

		// Loop through openList until we find the lowest cost node that is walkable.
		do {
			float temp = FLT_MAX;
			std::list<std::shared_ptr<Node>>::iterator itNode;
			for (std::list<std::shared_ptr<Node>>::iterator it = openList.begin(); it != openList.end(); it++) {
				std::shared_ptr<Node> n = *it;
				if (n->fCost < temp) {
					temp = n->fCost;
					itNode = it;
				}
			}
			
			node = *itNode;
			openList.erase(itNode);
			
			
		} while ( !openList.empty() && !allMap[x][y]->walkable);

		// Lowest cost node is added to list of visited nodes.
		x = node->x;
		y = node->y;
		if (x >= 0 && x < SCREEN_SIZE.x / TILE_SIZE.x && 
			y >= 0 && y < SCREEN_SIZE.y / TILE_SIZE.y) {
			closedList[x][y] = true;
		}

		for (auto newX = -1; newX <= 1; newX++) {
			for (auto newY = -1; newY <= 1; newY++) {
				double gNew, fNew, hNew;

				// Check that new node is within bounds.
				if (x + newX < 0 || y + newY < 0 ||
					x + newX >= SCREEN_SIZE.x / TILE_SIZE.x ||
					y + newY >= SCREEN_SIZE.y / TILE_SIZE.y) continue;

				// Early return. Make path if this is the destination.
				if (IsDestination(x + newX, y + newY, dest)) {

					allMap[x + newX][y + newY]->parentX = x;
					allMap[x + newX][y + newY]->parentY = y;

					 return MakePath(dest);
				}

				// If this is not walkable or has already been visited continue to next node.
				if (!allMap[x + newX][y + newY]->walkable || closedList[x + newX][y + newY])
					continue;

				// Calculate new value for node. Based on distance between node and destination.
				gNew = node->gCost + 1.0f;
				hNew = CalculateH(x + newX, y + newY, dest);
				fNew = gNew + hNew;

				// Add the new values to node map.
				if (allMap[x + newX][y + newY]->fCost == FLT_MAX ||
					allMap[x + newX][y + newY]->fCost > fNew) {

					allMap[x + newX][y + newY]->fCost = fNew;
					allMap[x + newX][y + newY]->gCost = gNew;
					allMap[x + newX][y + newY]->hCost = hNew;
					allMap[x + newX][y + newY]->parentX = x;
					allMap[x + newX][y + newY]->parentY = y;
					openList.emplace_back(allMap[x + newX][y + newY]);
				}
			}
		}
	}

	std::cout << "Destination was not found.";
	return empty;
}


