#include "deps/catch.h"

#include <chrono>
#include <thread>
#include <algorithm>
#include <functional>

#include "../src/sets.h"
#include "../src/sorters.h"
#include "../src/benchmark.h"
#include "../src/experiment.h"

TEST_CASE("set can be generated", "[set]") {
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
		auto set = sets::inverted(size);

		REQUIRE(set.size() == size);
	}
}

TEST_CASE("sort works as expected", "[sorter]") {
	constexpr size_t size = 128;
	auto set = sets::inverted(size);

	SECTION("insertion") {
		sorters::insertion(set.begin(), set.end());

		REQUIRE(std::is_sorted(set.begin(), set.end()));
	}

	SECTION("quick") {
		sorters::quick(set.begin(), set.end());

		REQUIRE(std::is_sorted(set.begin(), set.end()));
	}

	SECTION("heap") {
		sorters::heap(set.begin(), set.end());

		REQUIRE(std::is_sorted(set.begin(), set.end()));
	}

	SECTION("merge") {
		sorters::merge(set.begin(), set.end());

		REQUIRE(std::is_sorted(set.begin(), set.end()));
	}
}

TEST_CASE("experiment times with reasonable accuracy", "[experiment]") {
	constexpr auto duration = std::chrono::milliseconds(100);
	constexpr auto error_margin = std::chrono::milliseconds(5);

	const auto time = experiment([&] { std::this_thread::sleep_for(duration); }).run();

	REQUIRE((duration > time ? (duration - time) : (time - duration)) <= error_margin);
}

TEST_CASE("subset size generator works as expected", "[step type]") {
	REQUIRE(benchmark::detail::pow2(2, 1) == 2);
	REQUIRE(benchmark::detail::pow2(2, 2) == 4);

	const auto small_set_case = [](benchmark::step_type_t step_type) {
		const auto get_subset_size = benchmark::get_subset_size_factory(
			8, 16, step_type);

		for (int i = 1; i <= 16; i++) {
			if (i < 8) {
				REQUIRE(get_subset_size(i) == i);
			} else {
				REQUIRE(get_subset_size(i) == 8);
			}
		}
	};

	SECTION("linear") {
		small_set_case(benchmark::linear);

		constexpr auto large_linear = benchmark::get_subset_size_factory(
			256, 16, benchmark::linear);
		for (int i = 1; i <= 16; i++) {
			REQUIRE(large_linear(i) == i * (256 / 16));
		}
	}

	SECTION("quadratic") {
		small_set_case(benchmark::quadratic);

		constexpr auto large_quadratic = benchmark::get_subset_size_factory(
			256, 16, benchmark::quadratic);
		for (int i = 1; i <= 16; i++) {
			// Since 16^2 == 256 this is literally just f(x) = x^2.
			REQUIRE(large_quadratic(i) == i * i);
		}
	}
}
