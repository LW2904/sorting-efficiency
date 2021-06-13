#include <iterator>	// distance, begin, end, next
#include <algorithm>	// min_element, iter_swap, upper_bound, rotate, partition,
// inplace_merge, make_heap, sort_heap, is_heap, is_sorted
#include <functional>	// less, function

template<class I, class P>
void sorters::insertion(I first, I last, P cmp) {
	// TODO: Early test for containers with size < 2.

	for (auto it = first; it != last; ++it) {
		auto const insertion = std::upper_bound(first, it, *it, cmp);
		std::rotate(insertion, it, std::next(it));
	}
}

// TODO?: shell sort (taocp3, p. 83)
template<class I, class P>
void sorters::quick(I first, I last, P cmp) {
	auto const N = std::distance(first, last);
	if (N <= 1)
		return;

	auto const pivot = *std::next(first, N / 2);

	auto const middle1 = std::partition(first, last, [&, pivot](auto const &elem) {
		return cmp(elem, pivot);
	});
	auto const middle2 = std::partition(middle1, last, [&, pivot](auto const &elem) {
		return !cmp(pivot, elem);
	});

	quick(first, middle1, cmp);
	quick(middle2, last, cmp);
}

// TODO?: quick sort implementations with different pivot

// TODO?: bubble sort (p. 107)

template<class RI, class P>
void sorters::heap(RI first, RI last, P cmp) {
	std::make_heap(first, last, cmp);
	std::sort_heap(first, last, cmp);
}

// TODO?: (straight) selection sort (p. 139)
template<class BI, class P>
void sorters::merge(BI first, BI last, P cmp) {
	auto const N = std::distance(first, last);
	if (N <= 1)
		return;

	auto const middle = std::next(first, N / 2);

	merge(first, middle, cmp);
	merge(middle, last, cmp);

	std::inplace_merge(first, middle, last, cmp);
}

template<class I>
sorters::all_t<I> sorters::get_all() {
	return {
		{"quick",     sorters::quick<I>},
		{"heap",      sorters::heap<I>},
		{"merge",     sorters::merge<I>},
		{"insertion", sorters::insertion<I>},
	};
}
