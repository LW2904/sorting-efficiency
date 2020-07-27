# Sorting Efficiency

This is to be the backbone of a "pre-scientific paper" (don't ask me, [ask these guys](https://www.bmbwf.gv.at/en.html)) titled "Efficiency of Sorting Algorithms".

It is being written to answer the research question: "How does the theretical efficiency of selected sorting algorithms relate to the 'practical efficiency' of said algorithms?".

## Terminology

- `sorter`: an implementation of a sorting algorithm which is to be benchmarked. Always a function with the signature `void(I first, I last, P cmp = P{})` where `I` models any iterator and `P` defaults to `std::less`.

- `set`: a dataset on which a `sorter` is to be benchmarked. Always of type `std::vector<int>`.

## Contents

### Sorters

- `insertion`
- `quick`
- `heap`
- `merge`

These implementations _aren't_ excessively optimized for any metric. This means that there are certainly faster versions of these algorithms around. They do however rely strongly on the STL, which is (usually) heavily optimized and thoroughly tested, and which allows the implementations to be concise as well as easy to read and understand --- arguably one of the most important properties of an implementation.

### Sets

- `sorted`, initialized with `std::iota(..., 1)`
- `random`, a `std::random_shuffle`d `sorted`
- `partially_sorted`, 80% of `sorted` is randomly shuffled

## Building

- Make sure you have a C++17 conformant compiler and CMake installed.
- Clone the repository.
- Run `build.sh` in the root of the repository, a `build` folder will be created and populated.
- `build` will now contain an executable `sorting`

Tested on

- Arch Linux with GCC 10.1.0 and CMake 3.17.3
- Windows 10 (1903) with cl 19.22.27905 and CMake 3.16.5

## Testing

TODO.
