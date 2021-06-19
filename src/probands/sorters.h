#pragma once

#include <functional>	// function

namespace sorters {
	// Ideas for expansion: quick sort implementations with different pivot,
	// bubble sort, straight selection sort (à p. 139).

	template<class I, class P = std::less<>>
	using sorter_t = std::function<void(I, I, P)>;

	// Best: O(n), worst: O(n^2)
	template<class I, class P = std::less<>>
	void insertion(I first, I last, P cmp = P{});

	// Best: O(n log n), worst: O(n^2)
	template<class I, class P = std::less<>>
	void quick(I first, I last, P cmp = P{});

	// Always O(n log n)
	template<class RI, class P = std::less<>>
	void heap(RI first, RI last, P cmp = P{});

	// Always O(n log n)
	template<class BI, class P = std::less<>>
	void merge(BI first, BI last, P cmp = P{});
}

#include "sorters.hpp"
