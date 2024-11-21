#include "MathLib.h"

namespace MathLib {
	int LabLib3::findMax(int num_1, int num_2, int num_3) {
		int temp_num_1_2 = num_1 - num_2, temp_num_1_3 = num_1 - num_3, temp_num_2_3 = num_2 - num_3;
		if (temp_num_1_2 > 0 && temp_num_1_3 > 0) return num_1;
		if (temp_num_1_2 < 0 && temp_num_2_3>0) return num_2;
		return num_3;
	}

	int LabLib3::createIndexNum(int origin_num) {
		int result = 0, pose = origin_num < 0 ? 1 : 0;
		std::string temp_num = std::to_string(origin_num);
		for (int i = temp_num.length() - 1; i >= pose; i--) {
			if ((i + 1 - pose) % 2 == 0) result = result * 10 + (temp_num[i] - '0');
		}
		return result;
	}

	int LabLib3::findMinIndex(int origin_num) {
		int result = INT_MAX, pose = origin_num < 0 ? 1 : 0;
		std::string temp_num = std::to_string(origin_num);
		for (int i = pose; i < temp_num.length(); i++) {
			if (result > (temp_num[i] - '0')) result = temp_num[i] - '0';
		}
		return result;
	}

	int LabLib3::summUnderDiag(std::vector<std::vector<int>> arr) {
		int result = 0, rows = arr.size(), cols = arr[0].size();
		if (rows < 1 || cols < 1) throw "Format error: rows<1 || cols<1";
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols && j < i; j++) {
				if (arr[i][j] % 2 == 0) result += arr[i][j];
			}
		}
		return result;
	}
}