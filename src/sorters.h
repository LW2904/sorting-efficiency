#pragma once

#include "utils.h"

#include <functional>	// function

namespace sorters {
	template<class I, class P = std::less<>>
	using sorter_t = std::function<void(I, I, P)>;

	// Sorting by insertion

	// Best: O(n), worst: O(n^2)
	template<class I, class P = std::less<>>
	void insertion(I first, I last, P cmp = P{});

	// Sorting by exchanging

	// Best: O(n log n), worst: O(n^2)
	template<class I, class P = std::less<>>
	void quick(I first, I last, P cmp = P{});
	// TODO: quick sort implementations with different pivot
	// TODO: bubble sort (p. 107)

	// Sorting by selection

	// Always O(n log n)
	template<class RI, class P = std::less<>>
	void heap(RI first, RI last, P cmp = P{});
	// TODO: (straight) selection sort (p. 139)

	// Sorting by merging

	// Always O(n log n)
	template<class BI, class P = std::less<>>
	void merge(BI first, BI last, P cmp = P{});

	template<class I>
	using annotated_sorter_t = utils::annotated_t<sorters::sorter_t<I>>;
	template<class I>
	using all_t = std::vector<annotated_sorter_t<I>>;

	template<class I>
	all_t<I> get_all();
}

#include "sorters.hpp"
