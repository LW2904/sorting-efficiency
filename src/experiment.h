#include <vector>
#include <chrono>
#include <functional>

template<class A>
struct experiment {
	A algorithm;

	experiment(A algorithm) : algorithm(algorithm) { };

	auto run() {
		const auto start = std::chrono::steady_clock::now();

		algorithm();

		const auto end = std::chrono::steady_clock::now();

		return std::chrono::duration<double>{ end - start };
	}
};
