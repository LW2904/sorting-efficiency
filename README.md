# Sorting Efficiency

This is to be the backbone of a "pre-scientific paper" (don't ask me, [ask these guys](https://www.bmbwf.gv.at/en.html)) titled "Efficiency of Sorting Algorithms". It is being written to answer the research question: "How does the theoretical efficiency of selected sorting algorithms relate to the 'practical efficiency' of said algorithms?".

<p float="middle">
  <img src="https://github.com/fs-c/sorting-efficiency/blob/master/plots/md_insertion.png" width="390" />
  <img src="https://github.com/fs-c/sorting-efficiency/blob/master/plots/xs_sorted.png" width="390" /> 
</p>

---

This project implements

- an [`experiment` class](https://github.com/LW2904/sorting-efficiency/blob/master/src/experiment.h), which times an algorithm operating on a specific dataset.
- a number of ["sorters"](https://github.com/LW2904/sorting-efficiency/blob/master/src/sorters.h), i.e. implementations of sorting algorithms. Available are
  - insertion sort
  - quick sort
  - heap sort
  - merge sort
- [dataset generators](https://github.com/LW2904/sorting-efficiency/blob/master/src/sets.h), namely
  - sorted
  - inverted
  - random

including unit tests for each of the above.

## Usage

```
Usage: sorting [options]
Options:
  -h, --help        Display this information and exit.
  -o, --output      Sets the output path. (default: ./out)
  -s, --size        Sets the sample size. (default: 262144 i.e. 512^2)
```

The default (and currently _only_) behaviour is to generate files named `${sorter name}_${set name}` in the current working directory (you can change this with the `-o` option).

```
./build/sorting -o out
tree out
out
├── heap_inverted
├── heap_random
├── heap_sorted
├── insertion_inverted
├── insertion_random
...
```

These files contain numeric, tabular data in the format

```
cat out/heap_inverted
4096 2927.75
8192 5522.26
12288 9303.89
16384 13551.4
...
```

where the first row is the number of items sorted, and the second row is the time in milliseconds it took the sorter to do so. These files can be loaded as-is into applications like [gnuplot](http://www.gnuplot.info/). The two graphs at the top of this file, for example, were generated using the gnuplot scripts in the `scratch/` folder.

## Sorters

Sorters are functions with the signature `void(I first, I last, P cmp = P{})` where `I` models an Iterator and `P` models a Predicate (defaults to `std::less<>`).

These implementations _aren't_ excessively optimized for any metric. This means that there are certainly faster versions of these algorithms around. They do however rely strongly on the STL, which is (usually) heavily optimized and thoroughly tested, and which allows the implementations to be concise as well as easy to read and understand -- arguably one of the most important properties of an implementation.

## Sets

Datasets are of type `std::vector<int>`.

- `sorted`, initialized with `std::iota(..., 1)`
- `random`, a `std::shuffle`d `sorted`
- `inverted`, an inverted version of `sorted`

## Building

Make sure that you have a C++17 conformant compiler and CMake installed.

```
git clone https://github.com/LW2904/sorting-efficiency.git
mkdir build && cd build
cmake ..
make        # to build all targets
make test   # to run unit tests
```

You will find an executable named `sorting` in the `build` folder.

I've previously been able to compile and run on

- Arch Linux with GCC 10.1.0 and CMake 3.17.3
- Windows 10 (1903) with cl 19.22.27905 and CMake 3.16.5

