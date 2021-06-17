#include "config.h"
#include "utils/utils.h"
#include "probands/sets.h"
#include "probands/sorters.h"

#include <string>	// string
#include <cstdlib>	// EXIT_*

// Do this instead of set_name + '_' + sorter_name to avoid unnecessary
// allocations during concenation.
std::string get_result_path(const std::string &set_name, const std::string &sorter_name) {
	auto path = std::string{set_name};
	path += '_';
	path += sorter_name;

	return path;
}

int main(int, char *argv[]) {
	const config config{argv};

	// Get all sets and assign them a name
	const auto sets = std::map<std::string, sets::set_t>{
		{"sorted", sets::sorted(config.sample_size)},
		{"random", sets::random(config.sample_size)},
		{"inverted", sets::inverted(config.sample_size)},
	};

	// Get all sorters and assign them a name
	const auto sorters = std::map<std::string, benchmark::algorithm_t>{
		{"insertion", sorters::insertion<sets::iterator_t>},
		{"quick", sorters::quick<sets::iterator_t>},
		{"heap", sorters::heap<sets::iterator_t>},
		{"merge", sorters::merge<sets::iterator_t>},
	};

	// Generate a list of "tasks", i.e. benchmark runs, to be run
	std::multimap<std::string, benchmark> annotated_tasks;

	for (const auto &[set_name, set] : sets) {
		for (const auto &[sorter_name, sorter] : sorters) {
			const std::string path = get_result_path(set_name, sorter_name);
			const benchmark benchmark{set, sorter, config.step_type,
				config.total_chunks};

			for (size_t i = 0; i < config.runs; i++) {
				annotated_tasks.insert({path, benchmark});
			}
		}
	}

	// This is the reason that everything needs to be divided into tasks
	// so early, their order can now be randomized
	if (config.randomize_execution) {
		utils::random_shuffle(annotated_tasks.begin(), annotated_tasks.end());
	}

	// Run the tasks and undo any (potential) randomization by grouping them
	// by their key
	std::map<std::string, benchmark::result_group> annotated_result_groups;

	for (const auto &[path, benchmark] : annotated_tasks) {
		const auto result = benchmark.run();

		if (annotated_result_groups.count(path) == 0) {
			annotated_result_groups.insert({
				path, benchmark::result_group{std::vector<benchmark::result>{result}}
			});
		} else {
			annotated_result_groups[path].push_back(result);
		}
	}

	// Reduce the results to a single one per key and output them
	for (const auto &[path, result_group] : annotated_result_groups) {
		result_group.reduce(config.reduction_type).write(path);
	}

	return EXIT_SUCCESS;
}
