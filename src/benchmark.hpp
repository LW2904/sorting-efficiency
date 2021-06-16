#pragma once

constexpr auto benchmark::get_subset_size_factory(const size_t set_size,
	const size_t total_chunks, const step_type step_type
) {
	const auto power = step_type == linear || set_size <= total_chunks ? 1 : 2;

	// Determine the `a` in a function of the type f(x) = ax (for
	// the linear step type) or f(x) = ax^2 (for the quadratic one).
	const int a = set_size > total_chunks ? ((int) (
		set_size / detail::pow2(total_chunks, power)
	)) : 1;

	// Return a lambda which models f.
	return [a, power, set_size](const size_t i) constexpr {
		const auto value = a * detail::pow2(i, power);

		return value >= set_size ? set_size : value;
	};
}
