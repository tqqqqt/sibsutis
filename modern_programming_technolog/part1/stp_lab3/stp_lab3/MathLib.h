#pragma once

#include <string>
#include <vector>

namespace MathLib {
	class LabLib3 {
	public:
		static int findMax(int, int, int);
		int static createIndexNum(int);
		int static findMinIndex(int);
		int static summUnderDiag(std::vector<std::vector<int>>);
	};
}