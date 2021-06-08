#include "experiment.h"

experiment::result_t experiment::run() const {
	const auto start = std::chrono::steady_clock::now();

	algorithm();

	const auto end = std::chrono::steady_clock::now();

	return result_t{end - start};
}
