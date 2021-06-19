#include "benchmark.h"
#include "utils/experiment.h"

#include <fstream>
#include <filesystem>

ptrdiff_t benchmark::get_chunk_length(size_t chunk_index) const {
	return static_cast<ptrdiff_t>(
		this->step_type == benchmark::step_type_t::linear ? (
			this->linear_constant
		) : this->step_type == benchmark::step_type_t::quadratic ? (
			this->quadratic_constant
		) : (0) * chunk_index
	);
}

benchmark::result benchmark::run() const {
	benchmark::result result;

	for (size_t i = 0; i < this->total_chunks; i++) {
		const auto length = this->get_chunk_length(i);

		auto subset = sets::set_t{this->set.begin(),
			this->set.begin() + length};
		const auto time = experiment([&]() {
			this->algorithm(subset.begin(), subset.end(), std::less<>());
		}).run();

		result.emplace(length, time.count());
	}

	return result;
}

void benchmark::result::write(const std::string &path) const {
	if (std::filesystem::exists(path)) {
		std::filesystem::remove(path);
	}

	std::ofstream os{path};

	for (const auto &[n, time] : *this) {
		os << n << " " << time.count() << "\n";
	}
}

benchmark::result_group::rows_t benchmark::result_group::get_rows() const {
	rows_t rows;

	for (const auto &result : *this) {
		for (const auto &[size, time] : result) {
			if (rows.count(size) > 0) {
				rows[size].push_back(time);
			} else {
				rows[size] = rows_t::mapped_type(1, time);
			}
		}
	}

	return rows;
}

benchmark::result benchmark::result_group::reduce(
	benchmark::result_group::reduction_type reduction_type
) const {
	benchmark::result result;
	const auto &rows = this->get_rows();

	for (const auto &[size, times] : rows) {
		result[size] = reduction_type == reduction_type::average ? (
			benchmark::result_group::get_average(times)
		) : reduction_type == reduction_type::median ? (
			benchmark::result_group::get_median(times)
		) : experiment::duration_t{0};
	}

	return result;
}

experiment::duration_t benchmark::result_group::get_average(
	benchmark::result_group::durations_t durations
) {
	experiment::duration_t average{0};

	// Use online average algorithm since the offline version (sum / n) has
	// a decent chance of overflowing
	for (size_t i = 0; i < durations.size(); i++) {
		average += (durations.at(i) - average) / (i + 1);
	}

	return average;
}

experiment::duration_t benchmark::result_group::get_median(
	benchmark::result_group::durations_t durations
) {
	if (durations.empty()) {
		return experiment::duration_t{0};
	}

	const auto size = static_cast<ptrdiff_t>(durations.size());
	const auto target = durations.begin() + (size / 2);

	std::nth_element(durations.begin(), target, durations.end());

	if (size % 2) {
		return *target;
	} else {
		// Because std::nth_element guarantees that all elements preceding
		// target are <= *target.
		return (*target + *std::max_element(durations.begin(), target)) / 2;
	}
}
