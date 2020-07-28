#pragma once

#include "utils.h"

#include <vector>	// vector
#include <cstddef>	// size_t
#include <numeric>	// iota

namespace sets {

using set_t = std::vector<int>;
// For convenience
using iterator_t = set_t::iterator;

set_t sorted(const size_t size) {
	auto set = set_t(size);

	std::iota(set.begin(), set.end(), 1);

	return set;
}

set_t random(const size_t size) {
	auto set = sorted(size);

	utils::random_shuffle(set.begin(), set.end());

	return set;
}

}
