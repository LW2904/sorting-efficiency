#include "sets.h"
#include "../utils/utils.h"

#include <numeric>	// iota
#include <functional>	// function

// All subset of a set of a specific type are expected to have the same
// properties that the set is expected to have (i.e. being sorted, in reverse
// order, ...). This would be especially relevant if a "partially-sorted" set
// type is ever introduced.

sets::set_t sets::sorted(const size_t size) {
	auto set = set_t(size);

	std::iota(set.begin(), set.end(), 1);

	return set;
}

sets::set_t sets::inverted(const size_t size) {
	auto set = set_t(size);

	std::iota(std::rbegin(set), std::rend(set), 1);

	return set;
}

sets::set_t sets::random(const size_t size) {
	auto set = sorted(size);

	utils::random_shuffle(set.begin(), set.end());

	return set;
}
