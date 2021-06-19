#include "../src/benchmark.h"
#include "../src/probands/sorters.h"

TEST_CASE("sort works as expected", "[sorter]") {
	constexpr size_t size = 8;
	const auto sorted_set = sets::sorted(size);

	static const auto test_sort = [&](const benchmark::algorithm_t &algo) {
		auto set = sets::inverted(size);

		algo(set.begin(), set.end(), std::less<>{});

		REQUIRE(sorted_set == set);
	};

	SECTION("insertion") {
		test_sort(sorters::insertion<sets::iterator_t>);
	}

	SECTION("quick") {
		test_sort(sorters::quick<sets::iterator_t>);
	}

	SECTION("heap") {
		test_sort(sorters::merge<sets::iterator_t>);
	}

	SECTION("merge") {
		test_sort(sorters::heap<sets::iterator_t>);
	}
}