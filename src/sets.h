#pragma once

#include "utils.h"

#include <vector>	// vector
#include <cstddef>	// size_t

namespace sets {
	using set_t = std::vector<int>;
	// For convenience.
	using iterator_t = set_t::iterator;

	set_t sorted(size_t size);

	set_t inverted(size_t size);

	set_t random(size_t size);

	using annotated_set_t = utils::annotated_t<sets::set_t>;
	using all_t = std::vector<annotated_set_t>;

	all_t get_all(size_t set_size);
}
