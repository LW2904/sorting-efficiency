#pragma once

#include <iterator>	// distance, begin, end, next
#include <algorithm>	// min_element, iter_swap, upper_bound, rotate, partition,
			// inplace_merge, make_heap, sort_heap, is_heap, is_sorted
#include <functional>	// less, function

namespace sorters {

	template<class I, class P = std::less<>>
	using sorter_t = std::function<void(I, I, P)>;

	//
	// Sorting by insertion
	//

	// Best: O(n), worst: O(n^2)
	template<class I, class P = std::less<>>
	void insertion(I first, I last, P cmp = P{}) {
		// TODO: Early test for containers with size < 2.

		for (auto it = first; it != last; ++it) {
			auto const insertion = std::upper_bound(first, it, *it, cmp);
			std::rotate(insertion, it, std::next(it));
		}
	}

	// TODO: shell sort (taocp3, p. 83)

	//
	// Sorting by exchanging
	//

	// Best: O(n log n), worst: O(n^2)
	template<class I, class P = std::less<>>
	void quick(I first, I last, P cmp = P{}) {
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

	// TODO: quick sort implementations with different pivot

	// TODO: bubble sort (p. 107)

	//
	// Sorting by selection
	//

	// Always O(n log n)
	template<class RI, class P = std::less<>>
	void heap(RI first, RI last, P cmp = P{}) {
		std::make_heap(first, last, cmp);
		std::sort_heap(first, last, cmp);
	}

	// TODO: (straight) selection sort (p. 139)

	//
	// Sorting by merging
	//

	// Always O(n log n)
	template<class BI, class P = std::less<>>
	void merge(BI first, BI last, P cmp = P{}) {
		auto const N = std::distance(first, last);
		if (N <= 1)
			return;

		auto const middle = std::next(first, N / 2);

		merge(first, middle, cmp);
		merge(middle, last, cmp);

		std::inplace_merge(first, middle, last, cmp);
	}

}
