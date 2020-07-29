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

set_t inverted(const size_t size) {
	auto set = set_t(size);

	std::iota(std::rbegin(set), std::rend(set), 1);

	return set;
}

set_t random(const size_t size) {
	auto set = sorted(size);

	utils::random_shuffle(set.begin(), set.end());

	return set;
}

// TODO: This is experimental and designed to kill quicksort. It doesn't work, but I'm
// keeping it here because the concept has some merit, it just needs to be improved.
set_t anti_quick(const size_t size) {
	auto set = sorted(size);

	using I = iterator_t;
	std::function<void(I, I)> insert = [&](I first, I last) {
		const auto N = std::distance(first, last);

		if (N <= 64)
			return;

		*std::next(first, N / 2) = 1;

		insert(first, first + (N / 2));
		insert(first + (N / 2) + 1, last);
	};

	insert(set.begin(), set.end());

	return set;
}

}
