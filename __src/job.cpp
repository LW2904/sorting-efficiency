#include "job.h"

benchmark::result job::run(size_t total_chunks, size_t repetitions,
	job::reduction_type reduction, bool randomize
) const {
	// 1. Call benchmark::run a bunch of times, optionally in random order
	// 2. If runs > 1, reduce the results down to one based on the reduction type
}

benchmark::result job::reduce_results(const std::vector<benchmark::result> &results,
	job::reduction_type reduction
) {
	return benchmark::result();
}
