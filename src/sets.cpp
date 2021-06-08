#include "sets.h"

// Sets are expected to contain uniform numbers, i.e. if there ever is
// going to be a partially sorted set type, it would have to fit that
// criteria even (or rather, especially) if only a small continuous subset
// is examined.

sets::set_t sets::sorted(const size_t size) {
	auto set = set_t(size);

	std::iota(set.begin(), set.end(), 1);

	return set;
}

sets::set_t sets::inverted(const size_t size) {
	auto set = set_t(size);

	std::iota(std::rbegin(set), std::rend(set), 1);

	return set;
}

sets::set_t sets::random(const size_t size) {
	auto set = sorted(size);

	detail::random_shuffle(set.begin(), set.end());

	return set;
}

// This is experimental and designed to kill quicksort. It doesn't work,
// but I'm keeping it here because the concept has some merit, it just
// needs to be improved.
//
//	set_t anti_quick(const size_t size) {
//		auto set = sorted(size);
//
//		using I = iterator_t;
//		std::function<void(I, I)> insert = [&](I first, I last) {
//			const auto N = std::distance(first, last);
//
//			if (N <= 64)
//				return;
//
//			*std::next(first, N / 2) = 1;
//
//			insert(first, first + (N / 2));
//			insert(first + (N / 2) + 1, last);
//		};
//
//		insert(set.begin(), set.end());
//
//		return set;
//	}