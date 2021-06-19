#include "../src/utils/utils.h"
#include "../src/utils/experiment.h"

#include <thread>
#include <numeric>
#include <algorithm>

TEST_CASE("experiment times with reasonable accuracy", "[experiment]") {
	constexpr auto expected = std::chrono::milliseconds{100};
	constexpr auto error_margin = std::chrono::milliseconds{5};

	const auto time = experiment([&] {
		std::this_thread::sleep_for(expected);
	}).run();

	REQUIRE(expected >= (time - error_margin));
	REQUIRE(expected <= (time + error_margin));
}

TEST_CASE("random shuffle shuffles randomly", "[shuffle]") {
	std::vector<int> original{128};
	std::iota(original.begin(), original.end(), 4);

	auto copy = original;

	// Make sure the copy worked
	REQUIRE(copy == original);

	utils::random_shuffle(copy.begin(), copy.end());

	// It moved something at least
	REQUIRE(original != copy);

	// It didn't change the elements, only their order
	REQUIRE(std::is_permutation(copy.begin(), copy.end(), original.begin()));

	auto another_copy = original;
	utils::random_shuffle(another_copy.begin(), another_copy.end());

	// This is not a proper randomness test
	REQUIRE(copy != another_copy);
}

TEST_CASE("custom pow works as expected") {
	for (int i = 1; i < 20; i++) {
		REQUIRE(utils::pow2(i, 1) == i);
		REQUIRE(utils::pow2(i, 2) == i * i);
		// Only ^1 and ^2 are supported, anything else is undefined
	}
}
