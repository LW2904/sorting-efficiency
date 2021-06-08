#pragma once

#include <utility>
#include <vector>
#include <chrono>
#include <functional>

class experiment {
	std::function<void()> algorithm;

public:
	using time_t = double;
	using result_t = std::chrono::duration<time_t, std::micro>;

	explicit experiment(std::function<void()> algorithm)
		: algorithm(std::move(algorithm)) {};

	[[nodiscard]] result_t run() const;
};
