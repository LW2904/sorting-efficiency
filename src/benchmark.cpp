#include "benchmark.h"

benchmark::timings_t benchmark::run(algorithm_t algorithm, sets::set_t set,
	size_t total_chunks, step_type_t step_type
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
void benchmark::write(const std::string &sub_path, const std::string &algo_name,
	const std::string &set_name, const timings_t &timings
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

benchmark::timings_group::rows_t benchmark::timings_group::get_rows() {
	rows_t rows;

	for (const auto &timings : *this) {
		for (const auto &[size, time] : timings) {
			const auto casted_time = static_cast<experiment::time_t>(time);

			if (rows.count(size) > 0) {
				rows[size].push_back(casted_time);
			} else {
				rows[size] = rows_t::mapped_type(1, casted_time);
			}
		}
	}

	return rows;
}

benchmark::timings_t benchmark::timings_group::average() {
	const auto &rows = this->get_rows();
	timings_t final_timings;

	for (const auto &[size, times] : rows) {
		experiment::time_t average_time = 0;

		// Online average algorithm, since there's a chance that even int_64
		// would overflow if the offline algorithm (sum / n) were used.
		for (size_t i = 0; i < times.size(); i++) {
			const auto delta = times.at(i) - average_time;
			average_time += delta / static_cast<double>(i + 1);
		}

		final_timings[size] = average_time;
	}

	return final_timings;
}

benchmark::timings_t benchmark::timings_group::median() {
	const auto &rows = this->get_rows();
	timings_t final_timings;

	for (auto &[size, times] : rows) {
		rows_t::mapped_type times_copy{times};

		std::partial_sort(times_copy.begin(),
			times_copy.begin() + static_cast<ptrdiff_t>(times_copy.size() / 2),
			times_copy.end()
		);

		const auto median = times_copy.size() % 2 ? (
			times_copy[times_copy.size() / 2]
		) : (
			(times_copy[times_copy.size() / 2] + times_copy[times_copy.size() / 2 - 1]) / 2
		);

		final_timings[size] = median;
	}

	return final_timings;
}
