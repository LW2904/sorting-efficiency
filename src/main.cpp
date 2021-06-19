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

	const auto get_tasks = [&]() {
		std::vector<std::pair<std::string, benchmark>> tasks;

		for (const auto &[set_name, set] : sets) {
			for (const auto &[sorter_name, sorter] : sorters) {
				const std::string path = get_result_path(set_name, sorter_name);
				const benchmark benchmark{set, sorter, config.step_type,
					config.total_chunks};

				for (size_t i = 0; i < config.runs; i++) {
					tasks.emplace_back(path, benchmark);
				}
			}
		}

		return tasks;
	};

	// Generate a list of "tasks", i.e. benchmark runs, to be run
	const auto tasks = get_tasks();

	// Optionally randomize them
	if (config.randomize_execution) {
		utils::random_shuffle(tasks.begin(), tasks.end());
	}

	// Run them tasks and undo any (potential) randomization by grouping their
	// results by their key
	std::map<std::string, benchmark::result_group> result_groups;

	for (const auto &[path, benchmark] : tasks) {
		const auto result = benchmark.run();

		if (result_groups.count(path) == 0) {
			result_groups.insert({
				path, benchmark::result_group{std::vector<benchmark::result>{result}}
			});
		} else {
			result_groups[path].push_back(result);
		}
	}

	// Reduce the results to a single one per key and output them
	for (auto &[path, result_group] : result_groups) {
		const auto final_path = config.output + "/" + path;

		result_group.reduce(config.reduction_type).write(final_path);

		printf("wrote %s\n", path.c_str());
	}

	return EXIT_SUCCESS;
}
