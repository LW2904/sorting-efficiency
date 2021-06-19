#pragma once

#include <random>	// random_device, mt19937
#include <algorithm>	// shuffle

namespace utils {
	template <class I>
	void random_shuffle(I &&first, I &&last) {
		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(first, last, g);
	}

	// A version of pow from cmath that only works for y = 1 and y = 2.
	// Implemented because regular pow is not constexpr for whatever
	// reason. It's stupid that this needs to exist.
	constexpr auto pow2(const size_t x, const size_t y) {
		return y == 1 ? x : y == 2 ? x * x : 0;
	}
}
