#pragma once

#include "sets.h"
#include "sorters.h"
#include "experiment.h"

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

	enum step_type_t { linear, quadratic };

	auto get_step_generator(const size_t set_size, const size_t total_chunks,
		step_type_t step_type
	) {
		std::fesetround(FE_TONEAREST);

		// Determine the `a` in a function of the type f(x) = ax^2 + b where
		// f(total_chunks) = set_size. 
		const size_t a = set_size > total_chunks ? (
			std::nearbyint((
				step_type == quadratic ? sqrt(set_size) : set_size
			) / total_chunks)
		) : 1;

		// Return a lambda which models f
		return [&](size_t i) {
			return pow(a * (i + 1), step_type == quadratic ? 2 : 1);
		}
	}

	timings_t run(algorithm_t algorithm, sets::set_t set, int total_chunks,
		step_type_t step_type
	) {
		timings_t timings;

		const auto step_generator = get_step_generator(set.size(),
			total_chunks, step_type);

		for (size_t i = 0; i < total_chunks; i++) {
			auto subset_size = step_generator(i);

			auto subset = sets::set_t(set.begin(), set.begin() + subset_size);
			const auto time = experiment(std::bind(algorithm,
				subset.begin(), subset.end(), std::less<>())
			).run();

			timings.emplace(subset_size, time.count());
		}

		return timings;
	}

	// TODO: A class inheriting from std::ofstream with an overloaded <<
	// 	 operator would be significantly cleaner than this.
	// TODO: const char * should be std::string.
	void write(std::string sub_path, const char *algo_name, const char *set_name,
		timings_t timings) {
		std::filesystem::path file_path;

		if (sub_path.size())
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