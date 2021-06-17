#pragma once

#include <utility>	// move
#include <chrono>	// chrono
#include <functional>	// function

class experiment {
	std::function<void()> function;

public:
	using duration_t = std::chrono::steady_clock::duration;

	explicit experiment(std::function<void()> function)
		: function(std::move(function)) {};

	duration_t run() const;
};
