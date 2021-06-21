#include "experiment.h"

experiment::duration_t experiment::run() const {
	const auto start = clock_t::now();

	function();

	const auto end = clock_t::now();

	return duration_t{end - start};
}
