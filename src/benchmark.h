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
		// A version of pow from cmath that only works fo y = 1 and y = 2.
		// Implemented because regular pow _is not constexpr_ for whatever
		// reason. It's stupid that this needs to exist.
		constexpr auto pow2(const size_t x, const size_t y) {
			return y == 1 ? x : y == 2 ? x * x : 0;
		}
	}

	// Returns a function f, modeling the subset sizes given the total set size
	// and the requested amount of chunks. Since f should be thought of as a
	// function in the mathematical sense, the first subset size is f(1).
	// Values of f are always positive and always <= set_size.
	constexpr auto get_subset_size_factory(const size_t set_size, const size_t total_chunks,
		const step_type_t step_type
	) {
		const auto power = step_type == linear || set_size <= total_chunks ? 1 : 2;

		// Determine the `a` in a function of the type f(x) = ax (for
		// the linear step type) or f(x) = ax^2 (for the quadratic one).
		const int a = set_size > total_chunks ? ((int) (
			set_size / detail::pow2(total_chunks, power)
		)) : 1;

		// Return a lambda which models f.
		return [a, power, set_size](const size_t i) constexpr {
			const auto value = a * detail::pow2(i, power);

			return value >= set_size ? set_size : value;
		};
	}

	timings_t run(algorithm_t algorithm, sets::set_t set, size_t total_chunks,
		step_type_t step_type
	) {
		timings_t timings;

		const auto get_subset_size = get_subset_size_factory(set.size(),
			total_chunks, step_type);

		for (size_t i = 1; i <= total_chunks; i++) {
			auto subset_size = (std::ptrdiff_t) get_subset_size(i);

			auto subset = sets::set_t(set.begin(), set.begin() + subset_size);
			const auto time = experiment([&]() {
				algorithm(subset.begin(), subset.end(), std::less<>());
			}).run();

			timings.emplace(subset_size, time.count());
		}

		return timings;
	}

	// TODO: A class inheriting from std::ofstream with an overloaded <<
	// 	 operator would be significantly cleaner than this.
	// TODO: const char * should be std::string.
	void write(const std::string &sub_path, const char *algo_name,
		const char *set_name, const timings_t &timings
	) {
		std::filesystem::path file_path;

		if (!sub_path.empty())
			file_path += sub_path;

		file_path += "/";

		std::filesystem::create_directories(file_path);

		file_path += algo_name;
		file_path += "_";
		file_path += set_name;

		printf("writing %s\n", file_path.c_str());

		if (std::filesystem::exists(file_path)) {
			std::filesystem::remove(file_path);
		}

		std::ofstream os(file_path.c_str());

		for (const auto [n, t] : timings) {
			os << n << " " << t << "\n";
		}
	}
}
