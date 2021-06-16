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

	using result_t = std::map<size_t, experiment::time_t>;

	enum step_type {
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
		step_type step_type
	);

	result_t run(algorithm_t algorithm, sets::set_t set, size_t total_chunks,
		step_type step_type
	);

	void write(const std::string &sub_path, const std::string &algo_name,
		const std::string &set_name, const result_t &result
	);

	class result_group : public std::vector<benchmark::result_t> {
		using rows_t = std::map<benchmark::result_t::key_type, std::vector<
			benchmark::result_t::mapped_type>
		>;

		rows_t get_rows();

	public:
		result_t average();
		result_t median();
	};
}

#include "benchmark.hpp"
