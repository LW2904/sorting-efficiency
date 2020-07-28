#pragma once

#include "utils.h"

#include <vector>	// vector
#include <cstddef>	// size_t
#include <numeric>	// iota

namespace sets {

std::vector<int> sorted(const size_t size) {
	auto set = std::vector<int>(size);

	std::iota(set.begin(), set.end(), 1);

	return set;
}

std::vector<int> random(const size_t size) {
	auto set = sorted(size);

	utils::random_shuffle(set.begin(), set.end());

	return set;
}

}
