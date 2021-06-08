#pragma once

#include "sets.h"
#include "sorters.h"
#include "experiment.h"

#include <map>
#include <cmath>
#include <cfenv>
#include <cstdio>	// printf
#include <utility>
#include <fstream>
#include <filesystem>
#include <functional>	// bind

namespace benchmark {
	using algorithm_t = sorters::sorter_t<sets::iterator_t>;

	using timings_t = std::map<size_t, experiment::time_t>;

	enum step_type_t {
		linear, quadratic
	};

	namespace detail {
		// A version of pow from cmath that only works for y = 1 and y = 2.
		// Implemented because regular pow is not constexpr for whatever
		// reason. It's stupid that this needs to exist.
		constexpr auto pow2(const size_t x, const size_t y) {
			return y == 1 ? x : y == 2 ? x * x : 0;
		}
	}

	// Returns a function f, modeling the subset sizes given the total set size
	// and the requested amount of chunks. Since f should be thought of as a
	// function in the mathematical sense, the first subset size is f(1).
	// Values of f are always positive and always <= set_size.
	constexpr auto get_subset_size_factory(size_t set_size, size_t total_chunks,
		step_type_t step_type
	);

	timings_t run(algorithm_t algorithm, sets::set_t set, size_t total_chunks,
		step_type_t step_type
	);

	void write(const std::string &sub_path, const char *algo_name,
		const char *set_name, const timings_t &timings
	);
}

#include "benchmark.hpp"
