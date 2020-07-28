#include <vector>
#include <chrono>
#include <functional>

template<class I, class A>
struct experiment {
	I first;
	I last;

	A algorithm;

	experiment(I first, I last, A algorithm) : first(first),
		last(last), algorithm(algorithm) { };

	auto run() {
		const auto start = std::chrono::steady_clock::now();

		algorithm(first, last, std::less<>());

		const auto end = std::chrono::steady_clock::now();

		return std::chrono::duration<double>{ end - start };
	}
};
