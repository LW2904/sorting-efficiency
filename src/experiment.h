#pragma once

#include <utility>
#include <vector>
#include <chrono>
#include <functional>

class experiment {
	std::function<void()> algorithm;

public:
	using time_t = double;

	explicit experiment(std::function<void()> algorithm)
		: algorithm(std::move(algorithm)) { };

	auto run() const {
		const auto start = std::chrono::steady_clock::now();

		algorithm();

		const auto end = std::chrono::steady_clock::now();

		return std::chrono::duration<time_t, std::micro>{ end - start };
	}
};
