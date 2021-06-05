#pragma once

#include <algorithm>        // shuffle
#include <random>        // random_device, mt19937

namespace utils {
	// Since std::random_shuffle is deprecated
	template<class I>
	static void random_shuffle(I first, I last) {
		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(first, last, g);
	}
}
