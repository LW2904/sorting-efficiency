#include "sets.h"
#include "sorters.h"

#include <cstdio>

int main() {
	auto set = sets::random(20);

	sorters::quick(set.begin(), set.end());

	for (const auto s : set)
		printf("%d, ", s);

	putchar('\n');

	return 0;
}
