#include "benchmark.h"

benchmark::result_t benchmark::run(algorithm_t algorithm, sets::set_t set,
	size_t total_chunks, step_type_t step_type
) {
	result_t result;

	const auto get_subset_size = get_subset_size_factory(set.size(),
		total_chunks, step_type);

	for (size_t i = 1; i <= total_chunks; i++) {
		auto subset_size = (std::ptrdiff_t) get_subset_size(i);

		auto subset = sets::set_t(set.begin(), set.begin() + subset_size);
		const auto time = experiment([&]() {
			algorithm(subset.begin(), subset.end(), std::less<>());
		}).run();

		result.emplace(subset_size, time.count());
	}

	return result;
}

// TODO: A class inheriting from std::ofstream with an overloaded <<
// 	 operator would be significantly cleaner than this.
// TODO: const char * should be std::string.
void benchmark::write(const std::string &sub_path, const std::string &algo_name,
	const std::string &set_name, const result_t &result
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

	for (const auto [n, t] : result) {
		os << n << " " << t << "\n";
	}
}

benchmark::result_group::rows_t benchmark::result_group::get_rows() {
	rows_t rows;

	for (const auto &result : *this) {
		for (const auto &[size, time] : result) {
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

benchmark::result_t benchmark::result_group::average() {
	const auto &rows = this->get_rows();
	result_t final_result;

	for (const auto &[size, times] : rows) {
		experiment::time_t average_time = 0;

		// Online average algorithm, since there's a chance that even int_64
		// would overflow if the offline algorithm (sum / n) were used.
		for (size_t i = 0; i < times.size(); i++) {
			const auto delta = times.at(i) - average_time;
			average_time += delta / static_cast<double>(i + 1);
		}

		final_result[size] = average_time;
	}

	return final_result;
}

benchmark::result_t benchmark::result_group::median() {
	const auto &rows = this->get_rows();
	result_t final_result;

	for (auto &[size, times] : rows) {
		rows_t::mapped_type times_copy{times};

		// A partial sort would be enough.
		std::sort(times_copy.begin(), times_copy.end());

		const auto median = times_copy.size() % 2 ? (
			times_copy[times_copy.size() / 2]
		) : (
			(times_copy[times_copy.size() / 2] + times_copy[times_copy.size() / 2 - 1]) / 2
		);

		final_result[size] = median;
	}

	return final_result;
}
