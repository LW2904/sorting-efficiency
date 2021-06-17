#pragma once

#include <utility>

#include "benchmark.h"
#include "probands/sets.h"
#include "probands/sorters.h"

class job {
public:
	enum class reduction_type {
		average,
		median,
		none
	};

private:
	const sets::set_t &set;
	const benchmark::algorithm_t &algorithm;

	static benchmark::result reduce_results(const std::vector<benchmark::result> &results,
		job::reduction_type reduction);

public:
	job(const sets::set_t &set, const benchmark::algorithm_t &algorithm)
		: set(set), algorithm(algorithm) {};

	[[nodiscard]] benchmark::result run(size_t total_chunks, size_t repetitions,
		reduction_type reduction, bool randomize) const;
};
