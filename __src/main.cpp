#include "job.h"
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

using task = std::function<benchmark::result>;

int main(int, char *argv[]) {
	const config config{argv};

	const auto sets = std::map<std::string, sets::set_t>{
		{"sorted", sets::sorted(config.sample_size)},
		{"random", sets::random(config.sample_size)},
		{"inverted", sets::inverted(config.sample_size)},
	};

	const auto sorters = std::map<std::string, benchmark::algorithm_t>{
		{"insertion", sorters::insertion<sets::iterator_t>},
		{"quick", sorters::quick<sets::iterator_t>},
		{"heap", sorters::heap<sets::iterator_t>},
		{"merge", sorters::merge<sets::iterator_t>},
	};

	std::map<std::string, task> annotated_tasks;

	for (const auto &[set_name, set] : sets) {
		for (const auto &[sorter_name, sorter] : sorters) {
			const auto path = get_result_path(set_name, sorter_name);
			const auto runner = std::bind();
		}
	}

//	std::map<std::string, job> annotated_jobs;
//
//	for (const auto &[set_name, set] : sets) {
//		for (const auto &[sorter_name, sorter] : sorters) {
//			const auto path = get_result_path(set_name, sorter_name);
//			const job job = {set, sorter};
//
//			annotated_jobs.insert({path, job});
//		}
//	}
//
//	if (config.randomize_execution) {
//		utils::random_shuffle(annotated_jobs.begin(), annotated_jobs.end());
//	}
//
//	for (const auto &[path, job] : annotated_jobs) {
//		const auto result = job.run(config.total_chunks, config.runs,
//			config.reduction_type, config.randomize_execution);
//
//		result.write(path);
//	}

	return EXIT_SUCCESS;
}
