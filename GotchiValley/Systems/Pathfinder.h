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
		static std::vector<std::shared_ptr<Node>> findPath(const Node& actor, const Node& dest);

	private:
		static bool isDestination(const int32_t& x, const int32_t& y, const Node& dest);
		static double calculateH(const int32_t& x, const int32_t& y, const Node& dest);
		static std::vector<std::shared_ptr<Node>> makePath(const Node& dest);
	};


}