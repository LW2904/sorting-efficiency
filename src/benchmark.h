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
	enum class step_type_t {
		linear, quadratic
	} step_type;

	size_t total_chunks;

	// The result of running a benchmark
	struct result : public std::map<size_t, experiment::duration_t::rep> {
		void write(const std::string &path) const;
	};

	// Allows reducing a collection of benchmark results down to a single one
	struct result_group : public std::vector<benchmark::result> {
		enum class reduction_type {
			none, average, median
		};

		benchmark::result reduce(result_group::reduction_type reduction_type) const;
	};

	benchmark(sets::set_t set, algorithm_t algorithm, benchmark::step_type_t step_type,
		size_t total_chunks
	) : set(std::move(set)), algorithm(std::move(algorithm)), step_type(step_type),
		total_chunks(total_chunks) {};

	benchmark::result run() const;
};
