#pragma once
#include "GlobalVariables.h"
#include "LevelManager.h"
#include <iostream>
#include <array>
#include <cfloat>
#include <stack>

namespace GotchiValley {

	class Pathfinder {
	public:
		static std::vector<std::shared_ptr<Node>> FindPath(const Node& actor, const Node& dest);

	private:
		static bool IsDestination(const int32_t& x, const int32_t& y, const Node& dest);
		static double CalculateH(const int32_t& x, const int32_t& y, const Node& dest);
		static std::vector<std::shared_ptr<Node>> MakePath(const Node& dest);
	};


}