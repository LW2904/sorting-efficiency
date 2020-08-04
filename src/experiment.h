#include <utility>
#include <vector>
#include <chrono>
#include <functional>

struct experiment {
	std::function<void()> algorithm;

	explicit experiment(std::function<void()> algorithm)
	    : algorithm(std::move(algorithm)) { };

	auto run() const {
		const auto start = std::chrono::steady_clock::now();

		algorithm();

		const auto end = std::chrono::steady_clock::now();

		return std::chrono::duration<double, std::micro>{ end - start };
	}
};
