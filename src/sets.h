#pragma once

#include <vector>	// vector
#include <cstddef>	// size_t
#include <random>	// iota (although it should be in <algorithm>)
#include <algorithm>	// partial_sort, random_shuffle

namespace sets {

std::vector<int> sorted(const size_t size) {
	auto set = std::vector<int>(size);

	std::iota(set.begin(), set.end(), 1);

	return set;
}

std::vector<int> random(const size_t size) {
	auto set = sorted(size);

	std::random_shuffle(set.begin(), set.end());

	return set;
}

std::vector<int> partially_sorted(const size_t size) {
	auto set = sorted(size);

	std::random_shuffle(set.begin(), set.begin() + (size * 0.8));

	return set;
}

}
