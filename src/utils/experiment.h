#pragma once

#include <utility>	// move
#include <chrono>	// chrono
#include <functional>	// function

class experiment {
	std::function<void()> function;

	using clock_t = std::chrono::steady_clock;

public:
	using duration_t = clock_t::duration;

	explicit experiment(std::function<void()> function)
		: function(std::move(function)) {};

	[[nodiscard]] duration_t run() const;
};
