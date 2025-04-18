#pragma once
#include "GlobalVariables.h"
#include <iostream>
#include <array>
#include <cfloat>
#include <stack>

namespace GotchiValley {

	class Pathfinder {
	public:
		static std::vector<Node> FindPath(Node actor, Node dest);

	private:
		static bool IsValid(uint32_t x, uint32_t y);
		static bool IsDestination(uint32_t x, uint32_t y, Node dest);
		static double CalculateH(uint32_t x, uint32_t y, Node dest);
		static std::vector<Node> MakePath(std::array<std::array<Node, (SCREEN_SIZE.y / TILE_SIZE.y)>, (SCREEN_SIZE.x / TILE_SIZE.x)> &map, Node& dest);
		
	};


}