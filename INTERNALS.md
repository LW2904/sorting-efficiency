Large parts of the codebase (everything but `main.cpp`) are designed to be completely independent of each other. This is achieved through [templates](https://en.cppreference.com/w/cpp/language/templates) and [Named Requirements](https://en.cppreference.com/w/cpp/named_req) ([Container](https://en.cppreference.com/w/cpp/named_req/Container), [ForwardIterator](https://en.cppreference.com/w/cpp/named_req/ForwardIterator), ...) of templated variables. While these "Named Requirements" are _not enforced explicitly_ (although they might be [in the future](https://en.cppreference.com/w/cpp/language/constraints)), the following assumes that they are being followed.

## `experiment.h`

```cpp
class experiment {
	// ...

	using time_t = double;

	explicit experiment(std::function<void()> algorithm);

	auto run() const {
		// Use std::chrono::steady_clock to time the algorithm

		return std::chrono::duration<time_t, std::micro>{ end - start };
	}
};
```

The function `experiment::run` uses `std::chrono::steady_clock` to time the algorithm since it is [the most suitable clock for measuring intervals](https://en.cppreference.com/w/cpp/chrono/steady_clock).

## `sets.h`

```cpp
namespace sets {
	using set_t = std::vector<int>;
	using iterator_t = set_t::iterator;

	set_t sorted(const size_t size)                    { /* ... */ };
	set_t inverted(const size_t size)                  { /* ... */ };
	set_t random(const size_t size)	                   { /* ... */ };

	// ...
}
```

The [type alias](https://en.cppreference.com/w/cpp/language/type_alias) `sets::set_t` must be a [Container](https://en.cppreference.com/w/cpp/named_req/Container) (i.e. `std::vector`, `std::array`, ...) of elements which are [LessThanComparable](https://en.cppreference.com/w/cpp/named_req/LessThanComparable) (i.e. `int`, `double`, any type with an [overloaded `<` operator](https://en.cppreference.com/w/cpp/language/operators), ...).

## `sorters.h`

```cpp
namespace sorters {
	template <class I, class P = std::less<>>
	using sorter_t = std::function<void(I, I, P)>;

	template <class I, class P = std::less<>>
	void insertion(I first, I last, P cmp = P{})       { /* ... */ };

	template <class I, class P = std::less<>>
	void quick(I first, I last, P cmp = P{})           { /* ... */ };

	template<class RI, class P = std::less<>>
	void heap(RI first, RI last, P cmp = P{})          { /* ... */ };

	template <class BI, class P = std::less<>>
	void merge(BI first, BI last, P cmp = P{})         { /* ... */ };
}
```

_Reducing the obvious code duplication is a TODO._

- `I` must at least be a [ForwardIterator](https://en.cppreference.com/w/cpp/named_req/ForwardIterator),
- `RI` must be a [RandomAccessIterator](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator),
- `BI` must be a [BidirectionalIterator](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator) and
- `P` must be a [BinaryPredicate](https://en.cppreference.com/w/cpp/named_req/BinaryPredicate) or a [Compare](https://en.cppreference.com/w/cpp/named_req/Compare)

## `benchmark`

In `main.cpp`:

```cpp
using algorithm_t = sorters::sorter_t<sets::iterator_t>;

namespace benchmark {
	using timings_t = std::map<size_t, experiment::time_t>;

	timings_t run(algorithm_t algorithm, sets::set_t set, int total_chunks) {
		timings_t timings;
		const size_t set_size = set.size();
		const size_t chunk_size = /* calculate a good chunk size given
		                             the number of chunks requested  */

		for (size_t i = chunk_size; i <= set_size; i += chunk_size) {
			// ...
			const auto time = /* time the algorithm on a copy of the
                                             set which ranges from [0, i] */

			// `i` is the number of items sorted
			timings.emplace(i, time.count());
		}

		return timings;
	}

	void write(std::string sub_path, const char *algo_name, const char *set_name,
		timings_t timings) { /* ... */ }
}
```

## `main`

```cpp
int main(int, char *argv[]) {
	// ...

	auto sorters = std::map<const char *, algorithm_t>{
		{"quick", 	sorters::quick<sets::iterator_t>},
		// ...
	};

	const size_t set_size = cfg.sample_size;

	auto sets = std::map<const char *, sets::set_t>{
		{"sorted", 	sets::sorted(set_size)},
		// ...
	};

	for (auto [sorter_name, sorter] : sorters) {
		for (auto [set_name, set] : sets) {
			benchmark::write(cfg.output, sorter_name, set_name,
				benchmark::run(sorter, set, cfg.total_chunks));
		}
	}

	return 0;
}
```