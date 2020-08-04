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

void write_times(const char *sorter, const char *set, std::map<size_t, double> times) {
	static auto cur_path = std::filesystem::current_path();
	auto file_path = cur_path;

	file_path += "/";
	file_path += sorter;
	file_path += "_";
	file_path += set;

	printf("\tfile_path: %s\n", file_path.c_str());

	if (std::filesystem::exists(file_path)) {
		std::filesystem::remove(file_path);
	}

	std::ofstream os(file_path.c_str());

	for (const auto [n, t] : times) {
		os << n << " " << t << "\n";
	}
}

int main(int, char *argv[]) {
	config cfg{argv};

	auto sorters = std::map<const char *, sorters::sorter_t<sets::iterator_t>>{
		{"insertion", 	sorters::insertion<sets::iterator_t>},
		{"quick", 	sorters::quick<sets::iterator_t>},
		{"heap", 	sorters::heap<sets::iterator_t>},
		{"merge", 	sorters::merge<sets::iterator_t>},
	};

	constexpr size_t SET_SIZE = 512;
	constexpr size_t SET_CHUNKS = 128;
	constexpr size_t SET_CHUNK_SIZE = SET_SIZE / SET_CHUNKS;

	// TODO: DRY, write a set builder or something -- no need to pass SET_SIZE
	//	 to every single function.
	auto sets = std::map<const char *, sets::set_t>{
		{"sorted", 	sets::sorted(SET_SIZE)},
		{"random", 	sets::random(SET_SIZE)},
		{"inverted",	sets::inverted(SET_SIZE)},
	};

	if (cfg.output == config::output::human) {
		printf("unsupported option\n");

		return 1;
	}

	for (auto &[sorter_name, sorter] : sorters) {
		printf("%s sort\n", sorter_name);

		for (auto &[set_name, set] : sets) {
			auto times = std::map<size_t, double>{};

			for (size_t i = 0; i < SET_SIZE; i += SET_CHUNK_SIZE) {
				const auto time = experiment(
					std::bind(sorter,
						set.begin(),
						set.begin() + i, std::less<>()
					)
				).run();

				times.emplace(i, time.count());
			}

			write_times(sorter_name, set_name, times);
		}
	}

	return 0;
}
