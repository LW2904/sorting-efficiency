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
}
