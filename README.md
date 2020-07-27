# Sorting Efficiency

## Terminology

- `sorter`: an implementation of a sorting algorithm which is to be benchmarked. Always a function with the signature `void(I first, I last, P cmp = P{})` where `I` models any iterator and `P` defaults to `std::less`.

- `set`: a dataset on which a `sorter` is to be benchmarked. Always of type `std::vector<int>`.

## Contents

### Sorters

- `insertion`
- `quick`
- `heap`
- `merge`

### Sets

- `sorted`, initialized with `std::iota(..., 1)`
- `random`, a `std::random_shuffle`d `sorted`
- `partially_sorted`, 80% of `sorted` is randomly shuffled

## Building

Tested on Arch Linux with GCC 10.1.0 and CMake 3.17.3.

- Make sure you have a C++17 conformant compiler and CMake installed.
- Clone the repository.
- Run `build.sh` in the root of the repository, a `build` folder will be created and populated.
- `build` will now contain an executable `sorting`

## Testing

TODO.
