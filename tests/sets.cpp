#include "../src/probands/sets.h"

#include <algorithm>	// is_sorted

TEST_CASE("set is as a expected", "[set]") {
	constexpr size_t size = 128;

	SECTION("sorted") {
		auto set = sets::sorted(size);

		REQUIRE(set.size() == size);
		REQUIRE(std::is_sorted(set.begin(), set.end()));
	}

	SECTION("inverted") {
		auto set = sets::inverted(size);

		REQUIRE(set.size() == size);
		REQUIRE(std::is_sorted(set.begin(), set.end(), std::greater<>()));
	}

	SECTION("random") {
		auto set = sets::random(size);

		REQUIRE(set.size() == size);
		// Make sure random sets are actually random.
		// TODO?: This is not a proper randomness test.
		REQUIRE(set != sets::random(size));
	}
}
