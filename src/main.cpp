#include "sets.h"
#include "config.h"
#include "sorters.h"
#include "benchmark.h"

#include <map>		// map
#include <cstdio>	// printf

int main(int, char *argv[]) {
	config cfg{argv};

	if (cfg.should_exit) {
		return 1;
	}

	auto sorters = std::map<const char *, benchmark::algorithm_t>{
		{"quick",     sorters::quick<sets::iterator_t>},
		{"heap",      sorters::heap<sets::iterator_t>},
		{"merge",     sorters::merge<sets::iterator_t>},
		{"insertion", sorters::insertion<sets::iterator_t>},
	};

	const size_t set_size = cfg.sample_size;

	auto sets = std::map<const char *, sets::set_t>{
		{"sorted",   sets::sorted(set_size)},
		{"random",   sets::random(set_size)},
		{"inverted", sets::inverted(set_size)},
	};

	printf("sorting %ld elements\n", set_size);

	for (auto [sorter_name, sorter] : sorters) {
		for (auto [set_name, set] : sets) {
			benchmark::write(cfg.output, sorter_name, set_name,
				benchmark::run(sorter, set, cfg.total_chunks,
					cfg.step_type));
		}
	}

	return 0;
}
