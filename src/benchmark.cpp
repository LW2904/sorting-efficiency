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
void benchmark::write(const std::string &sub_path, const char *algo_name,
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
