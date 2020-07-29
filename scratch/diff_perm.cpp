/**
 * Outputs the absolute difference of the elements (i.e. 5 for {1, 3, 2, 4}) of 
 * all permutations of a vector.
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

int main() {
	auto vec = std::vector<int>{ 0, 1, 2, 3, 4 };

	int perm_i = 0;
	while (std::next_permutation(vec.begin(), vec.end()) && ++perm_i) {
		int diff = 0;

		for (size_t i = 1; i < vec.size(); i++)
			diff += std::abs(vec.at(i) - vec.at(i - 1));

		std::cout << perm_i << ": " << diff << "\n";
	}

	return 0;
}
