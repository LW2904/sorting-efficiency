#pragma once

#include <random>	// random_device, mt19937
#include <algorithm>	// shuffle

namespace utils {
	// Since std::random_shuffle is deprecated (for whatever reason)
	template<class I>
	void random_shuffle(I &&first, I &&last) {
		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(first, last, g);
	}

	using annotate_t = std::string;
	template<class T>
	using annotated_t = std::pair<annotate_t, T>;
}
