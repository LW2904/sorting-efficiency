#pragma once

#include <vector>	// vector
#include <cstddef>	// size_t
#include <random>	// random_device, mt19937, uniform_int_distribution

namespace sets {

std::vector<int> random(const size_t size) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, size);

	auto set = std::vector<int>(size);

	for (size_t s = 0; s < size; s++)
		set.at(s) = dist(gen);

	return set;
}

}
