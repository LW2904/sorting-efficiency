#include "../src/utils/experiment.h"

#include <thread>
#include <cstdlib>

TEST_CASE("experiment times with reasonable accuracy", "[experiment]") {
	constexpr auto expected = std::chrono::milliseconds{100};
	constexpr auto error_margin = std::chrono::milliseconds{5};

	const auto time = experiment([&] {
		std::this_thread::sleep_for(expected);
	}).run();

	REQUIRE(expected >= (time - error_margin));
	REQUIRE(expected <= (time + error_margin));
}