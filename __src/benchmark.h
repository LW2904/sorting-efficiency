#pragma once

#include "probands/sets.h"
#include "probands/sorters.h"
#include "utils/experiment.h"

#include <map>		// map
#include <string>	// string
#include <utility>	// move

class benchmark {
public:
	// The kind of function that can be benchmarked
	using algorithm_t = sorters::sorter_t<sets::iterator_t>;

private:
	sets::set_t set;
	algorithm_t algorithm;

	size_t get_chunk_length(size_t chunk_index);

public:
	enum class step_type {
		linear, quadratic
	};

	// The result of running a benchmark
	struct result : public std::map<size_t, experiment::duration_t::rep> {
		void write(const std::string &path) const;
	};

	benchmark(sets::set_t set, algorithm_t algorithm) : set(std::move(set)),
		algorithm(std::move(algorithm)) {};

	result run(size_t total_chunks, step_type step_type);
};
