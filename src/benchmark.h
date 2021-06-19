#pragma once

#include "probands/sets.h"
#include "probands/sorters.h"
#include "utils/utils.h"
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

	size_t linear_constant;
	size_t quadratic_constant;
	[[nodiscard]] ptrdiff_t get_chunk_length(size_t chunk_index) const;

public:
	enum class step_type_t {
		linear, quadratic
	} step_type;

	size_t total_chunks{};

	// The result of running a benchmark
	struct result : public std::map<size_t, experiment::duration_t> {
		void write(const std::string &path) const;
	};

	// Allows reducing a collection of benchmark results down to a single one
	class result_group : public std::vector<benchmark::result> {
		using durations_t = std::vector<benchmark::result::mapped_type>;
		using rows_t = std::map<benchmark::result::key_type, durations_t>;

		static durations_t::value_type get_average(durations_t durations) ;
		static durations_t::value_type get_median(durations_t durations) ;

		[[nodiscard]] rows_t get_rows() const;

	public:
		enum class reduction_type {
			none, average, median
		};

		[[nodiscard]]
		benchmark::result reduce(result_group::reduction_type reduction_type) const;
	};

	benchmark(sets::set_t set, algorithm_t algorithm, benchmark::step_type_t step_type,
		size_t total_chunks
	) : set(std::move(set)), algorithm(std::move(algorithm)), step_type(step_type),
		total_chunks(total_chunks)
	{
		this->linear_constant = this->set.size() / this->total_chunks;
		this->quadratic_constant = static_cast<ptrdiff_t>(
			this->set.size() / utils::pow2(this->total_chunks, 2));
	}

	[[nodiscard]] benchmark::result run() const;
};
