#include "sets.h"
#include "sorters.h"
#include "experiment.h"

#include <map>
#include <cstdio>

int main() {
	auto sorters = std::map<const char *, sorters::sorter_t<sets::iterator_t>>{
		{"insertion", 	sorters::insertion<sets::iterator_t>},
		{"quick", 	sorters::quick<sets::iterator_t>},
		{"heap", 	sorters::heap<sets::iterator_t>},
		{"merge", 	sorters::merge<sets::iterator_t>},
	};

	constexpr size_t SET_SIZE = 512 * 512;

	// TODO: DRY, write a set builder or something -- no need to pass SET_SIZE
	//	 to every single function.
	auto sets = std::map<const char *, sets::set_t>{
		{"sorted", 	sets::sorted(SET_SIZE)},
		{"random", 	sets::random(SET_SIZE)},
	};

	for (auto &[sorter_name, sorter] : sorters) {
		printf("%s sort\n", sorter_name);

		for (auto &[set_name, set] : sets) {
			const auto time = experiment(set.begin(), set.end(), sorter)
				.run();

			printf("\t%s set: %f s\n", set_name, time);
		}
	}

	return 0;
}
