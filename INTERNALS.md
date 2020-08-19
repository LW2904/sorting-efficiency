The following three parts are fully generic:

- the `experiment` class times a function of type `void()` using `std::chrono::steady_clock`, which is [the most suitable clock for measuring intervals](https://en.cppreference.com/w/cpp/chrono/steady_clock).

- the `sets` namespace contains various set generators (sorted, inverted, random) which are functions of type `sets::set_t(const size_t)`. Currently, `sets::set_t` is defined to be `std::vector<int>` -- it could be redefined to any [Container](https://en.cppreference.com/w/cpp/named_req/Container) containing [LessThanComparable](https://en.cppreference.com/w/cpp/named_req/LessThanComparable) elements.

- the `sorters` namespace contains implementations of various sorting algorithms (insertion, quick, heap, merge) which are functions of type `void(I begin, I end, P)` (aliased as `sorters::sorter_t`) where `I` is an iterator (at least [ForwardIterator](https://en.cppreference.com/w/cpp/named_req/ForwardIterator)) and `P` is a [BinaryPredicate](https://en.cppreference.com/w/cpp/named_req/BinaryPredicate) (it defaults to `std::less<>`).

Tying them together is the `benchmark` namespace, which provides a `run` function that takes a function of type `sorters::sorter_t` and a container of type `sets::set_t`. It creates subsets of the given container with increasing size (i. e. sets containing [0, ..., 16], [0, ..., 32], [0, ..., 48], ... elements of the original container) and uses the `experiment` class to measure the execution time of the given algorithm with each subset.

```C++
const size_t chunk_size = set_size > total_chunks ?
	std::nearbyint(set_size / total_chunks) : 1;

for (size_t i = chunk_size; i <= set_size; i += chunk_size) {
	// Important: We have to operate on a _copied subset_.
	auto subset = S(set.begin(), set.begin() + i);
	const auto time = experiment(std::bind(algorithm,
		subset.begin(), subset.end(), std::less<>())
	).run();

	timings.emplace(i, time.count());
}
```

It returns a Container of type `benchmark::timings_t` which can be written to a file using the `benchmark::write` function.

The main function contains the following piece of code

```C++
auto sorters = std::map<const char *, sorters::sorter_t<sets::iterator_t>>{
	{"quick", 	sorters::quick<sets::iterator_t>},
	// ...
};

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
```

which runs and writes a benchmark for each unique pair in `sorters X sets` (cartesian product).
