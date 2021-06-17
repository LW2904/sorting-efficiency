#include "benchmark.h"

size_t benchmark::get_chunk_length(size_t chunk_index) {
	return 0;
}

benchmark::result benchmark::run() const {
	return benchmark::result();
}

void benchmark::result::write(const std::string &path) const {

}

benchmark::result benchmark::result_group::reduce(
	benchmark::result_group::reduction_type reduction_type
) {
	return benchmark::result();
}
