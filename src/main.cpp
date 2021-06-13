#include "sets.h"
#include "utils.h"
#include "config.h"
#include "sorters.h"
#include "benchmark.h"

#include <map>		// map
#include <tuple>	// tuple, get
#include <cstdio>	// printf
#include <utility>

enum status: int {
	SUCCESS = 0,
	INVALID_CONFIG = 1,
	INVALID_STATE = 2,
};

struct task {
	sorters::annotated_sorter_t<sets::iterator_t> sorter;
	sets::annotated_set_t set;

	benchmark::timings_t result;

	task(sorters::annotated_sorter_t<sets::iterator_t> sorter,
		sets::annotated_set_t set
	) : sorter(std::move(sorter)), set(std::move(set)) {};

	void run(const size_t total_chunks, const benchmark::step_type_t step_type) {
		this->result = benchmark::run(sorter.second, set.second,
			total_chunks, step_type);
	}
};

auto get_tasks(const sorters::all_t<sets::iterator_t> &sorters,
	const sets::all_t &sets, const size_t runs, const bool randomize
) {
	std::vector<task> tasks;

	for (const auto &sorter : sorters) {
		for (const auto &set : sets) {
			for (size_t i = 0; i < runs; i++) {
				tasks.emplace_back(sorter, set);
			}
		}
	}

	if (randomize) {
		utils::random_shuffle(tasks.begin(), tasks.end());
	}

	return tasks;
}

int main(int, char *argv[]) {
	config cfg{argv};

	if (cfg.should_exit) {
		return status::INVALID_CONFIG;
	}

	// Get sorters and sets

	const auto sorters = sorters::get_all<sets::iterator_t>();
	const auto sets = sets::get_all(cfg.sample_size);

	// Generate tasks with the available sorters/sets and the given config

	const size_t runs = std::max(std::max(cfg.average, cfg.median),
		static_cast<size_t>(1));
	auto tasks = get_tasks(sorters, sets, runs, cfg.randomize_tasks);

	// Run the tasks and group them by sorter and set (the order of tasks
	// is arbitrary)

	std::map<utils::annotate_t, std::map<utils::annotate_t, std::vector<task>>>
		raw_results;

	for (auto &task : tasks) {
		task.run(cfg.total_chunks, cfg.step_type);

		raw_results[task.sorter.first][task.set.first].push_back(task);
	}

	// Consolidate task results into a ready-to-output format

	std::vector<std::tuple<utils::annotate_t, utils::annotate_t, benchmark::timings_t>>
	        results;

	for (const auto &sorter : raw_results) {
		for (const auto &set : sorter.second) {
			benchmark::timings_group timings;

			for (const auto &task : set.second) {
				timings.push_back(task.result);
			}

			if (timings.empty()) {
				printf("error: no timings for sorter %s with"
				       "set %s\n", sorter.first.c_str(),
				       set.first.c_str());

				return status::INVALID_STATE;
			}

			results.emplace_back(sorter.first, set.first, (
				timings.size() == 1 ? timings.at(0) : (
					cfg.average ? timings.average() :
					cfg.median ? timings.median() : timings.at(1)
				)
			));
		}
	}

	// Output the consolidated results

	for (const auto &result : results) {
		benchmark::write(cfg.output, std::get<0>(result),
		        std::get<1>(result), std::get<2>(result));
	}

	const auto write_run_info = [&]() {
		std::filesystem::path file_path;
		file_path += cfg.output + "/info";
		std::ofstream ostrm(file_path);

		ostrm << "tasks:\n";

		for (const auto &task : tasks) {
			ostrm << "\t" << task.sorter.first << " with " << task.set.first << "\n";
		}
	};

	if (cfg.write_run_info) {
		write_run_info();
	}

	return status::SUCCESS;
}
