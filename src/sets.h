#pragma once

#include <vector>	// vector
#include <cstddef>	// size_t
#include <numeric>	// iota
#include <functional>	// function
#include <random>	// random_device, mt19937

namespace sets {
	using set_t = std::vector<int>;
	// For convenience.
	using iterator_t = set_t::iterator;

	namespace detail {
		// Since std::random_shuffle is deprecated
		template<class I>
		void random_shuffle(I first, I last) {
			std::random_device rd;
			std::mt19937 g(rd());

			std::shuffle(first, last, g);
		}
	}

	set_t sorted(size_t size);

	set_t inverted(size_t size);

	set_t random(size_t size);
}
