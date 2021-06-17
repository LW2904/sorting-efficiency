#pragma once

#include <vector>	// vector
#include <cstddef>	// size_t

namespace sets {
	using set_t = std::vector<int>;
	// For convenience.
	using iterator_t = set_t::iterator;

	set_t sorted(size_t size);

	set_t inverted(size_t size);

	set_t random(size_t size);
}
