#include "experiment.h"

experiment::duration_t experiment::run() const {
	const auto start = std::chrono::steady_clock::now();

	function();

	const auto end = std::chrono::steady_clock::now();

	return duration_t{end - start};
}
