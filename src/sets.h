#pragma once

#include <vector>	// vector
#include <random>	// random_device, mt19937
#include <cstddef>	// size_t
#include <numeric>	// iota
#include <algorithm>	// partial_sort, random_shuffle

namespace sets {

// Since std::random_shuffle is deprecated
template<class I>
static void random_shuffle(I first, I last) {
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(first, last, g);
}

std::vector<int> sorted(const size_t size) {
	auto set = std::vector<int>(size);

	std::iota(set.begin(), set.end(), 1);

	return set;
}

std::vector<int> random(const size_t size) {
	auto set = sorted(size);

	sets::random_shuffle(set.begin(), set.end());

	return set;
}

std::vector<int> partially_sorted(const size_t size) {
	auto set = sorted(size);

	std::random_device rd;
	std::mt19937 g(rd());

	sets::random_shuffle(set.begin(), set.begin() + (size * 0.8));

	return set;
}

}
