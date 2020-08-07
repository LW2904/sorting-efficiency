#include "sets.h"
#include "config.h"
#include "sorters.h"
#include "experiment.h"

#include <map>		// map
#include <cstdio>	// printf
#include <fstream>
#include <utility>	// pair
#include <functional>	// bind
#include <filesystem>

namespace benchmark {
	using timings_t = std::map<size_t, experiment::time_t>;

	template<class A, class S>
	timings_t run(A algorithm, S set) {
		timings_t timings;

		const size_t set_size = set.size();
		const size_t chunk_size = set_size / 64;

		for (size_t i = 0; i < set_size; i += chunk_size) {
			// Important: We have to operate on a _copied subset_.
			auto subset = S(set.begin(), set.begin() + i);
			const auto time = experiment(std::bind(algorithm,
				subset.begin(), subset.end(), std::less<>())
			).run();

			timings.emplace(i, time.count());
		}

		return timings;
	}

	// TODO: A class inheriting from std::ofstream with an overloaded <<
	// 	 operator would be significantly cleaner than this.
	// TODO: const char * should be std::string.
	void write(std::string sub_path, const char *algo_name, const char *set_name,
		timings_t timings) {
		static auto cur_path = std::filesystem::current_path();
		auto file_path = cur_path;

		file_path += "/";

		if (sub_path.size())
			file_path += sub_path;

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

int main(int, char *argv[]) {
	config cfg{argv};

	if (cfg.should_exit) {
		return 1;
	}

	auto sorters = std::map<const char *, sorters::sorter_t<sets::iterator_t>>{
		{"quick", 	sorters::quick<sets::iterator_t>},
		{"heap", 	sorters::heap<sets::iterator_t>},
		{"merge", 	sorters::merge<sets::iterator_t>},
		{"insertion", 	sorters::insertion<sets::iterator_t>},
	};

	constexpr size_t set_size = 512 * 512;

	auto sets = std::map<const char *, sets::set_t>{
		{"sorted", 	sets::sorted(set_size)},
		{"random", 	sets::random(set_size)},
		{"inverted",	sets::inverted(set_size)},
	};

	for (auto [sorter_name, sorter] : sorters) {
		for (auto [set_name, set] : sets) {
			benchmark::write(cfg.output, sorter_name, set_name,
				benchmark::run(sorter, set));
		}
	}

	return 0;
}
