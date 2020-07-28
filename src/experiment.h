#include <vector>
#include <chrono>
#include <functional>

// TODO: These shouldn't be here.

using P = std::less<>;
using I = std::vector<int>::iterator;
using algorithm_t = std::function<void(I, I, P)>;

using set_t = std::vector<int>;

struct experiment {
	set_t set;

	algorithm_t algorithm;

	experiment(set_t set, algorithm_t algorithm) : set(set),
		algorithm(algorithm) {};

	auto run() {
		const auto start = std::chrono::steady_clock::now();

		algorithm(set.begin(), set.end(), std::less<>());

		const auto end = std::chrono::steady_clock::now();

		return std::chrono::duration<double>{ end - start };
	}
};
