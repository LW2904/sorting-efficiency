#include "sets.h"
#include "sorters.h"

#include <map>
#include <chrono>
#include <cstdio>

// TODO: These shouldn't be here.

using P = std::less<>;
using I = std::vector<int>::iterator;
using algorithm_t = std::function<void(I, I, P)>;

using set_t = std::vector<int>;

struct experiment {
	set_t set;

	algorithm_t algorithm;

	experiment(std::vector<int> set, algorithm_t algorithm) : set(set),
		algorithm(algorithm) {};

	auto run() {
		const auto start = std::chrono::steady_clock::now();

		algorithm(set.begin(), set.end(), std::less<>());

		const auto end = std::chrono::steady_clock::now();

		return std::chrono::duration<double>{ end - start };
	}
};

int main() {
	// TODO: DRY, maybe have them all default to std::vector<int>::iterator?
	auto sorters = std::map<const char *, algorithm_t>{
		{"insertion", 	sorters::insertion<set_t::iterator>},
		{"quick", 	sorters::quick<set_t::iterator>},
		{"heap", 	sorters::heap<set_t::iterator>},
		{"merge", 	sorters::merge<set_t::iterator>},
	};

	constexpr size_t SET_SIZE = 512 * 512;

	// TODO: DRY, write a set builder or something -- no need to pass SET_SIZE
	//	 to every single function.
	auto sets = std::map<const char *, set_t>{
		{"sorted", 		sets::sorted(SET_SIZE)},
		{"partially sorted", 	sets::partially_sorted(SET_SIZE)},
		{"random", 		sets::random(SET_SIZE)},
	};

	for (auto &[sorter_name, sorter] : sorters) {
		printf("%s sort\n", sorter_name);

		for (auto &[set_name, set] : sets) {
			const auto time = experiment(set, sorter).run();

			printf("\t%s set: %f s\n", set_name, time);
		}
	}

	return 0;
}
