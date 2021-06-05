# Sorting Efficiency

This is to be the backbone of a "pre-scientific paper" (don't ask me, [ask these guys](https://www.bmbwf.gv.at/en.html)) titled "Efficiency of Sorting Algorithms". It is being written to answer the research question: "How does the theoretical efficiency of selected sorting algorithms relate to the 'practical efficiency' of said algorithms?".

<p float="middle">
  <img src="https://github.com/fs-c/sorting-efficiency/blob/master/example/plots/md_insertion.png" width="390" />
  <img src="https://github.com/fs-c/sorting-efficiency/blob/master/example/plots/xs_sorted.png" width="390" /> 
</p>

---

This project implements

- an [`experiment` class](https://github.com/LW2904/sorting-efficiency/blob/master/src/experiment.h), which times an algorithm operating on a specific dataset.
- a number of ["sorters"](https://github.com/LW2904/sorting-efficiency/blob/master/src/sorters.h), i.e., implementations of sorting algorithms. Available are
  - insertion sort
  - quick sort
  - heap sort
  - merge sort
- [set generators](https://github.com/LW2904/sorting-efficiency/blob/master/src/sets.h), namely
  - sorted
  - inverted
  - random
- different chunk size generators
  - linear
  - quadratic

including unit tests for each of the above.

## Usage

```
$ benchmark -h
Usage: benchmark [options]
Options:
  -h, --help        Display this information and exit.
  -o, --output      Sets the output path. (default: ./out)
  -s, --size        Sets the sample size. (default: 262144 i.e. 2^18)
  -c, --chunks      Sets the number of chunks that the set will be devided into.
                    (default: 128)
  -t, --step-type   Specifies the step type to use, one of 'linear' or
                    'quadratic'. (default: linear)
```

The default (and _only_) behaviour is to generate files named `${sorter name}_${set name}` in the `./out/` directory (you can change this with the `-o` option).

```
$ benchmark -o example/data
$ tree example/data
data
├── heap_inverted
├── heap_random
├── heap_sorted
├── insertion_inverted
├── insertion_random
└── ...
```

These files contain numeric, tabular data in the format

```
$ cat example/data/heap_inverted
2048 1905.09
4096 4085.3
6144 6398.93
...
258048 367263
260096 359454
262144 369991
```

where the first column is the number of items sorted, and the second column is the time in microseconds it took the sorter to do so. By default, there are 128 chunks (rows), this can be changed with the `-c` option.

These files can be loaded as-is into applications like [gnuplot](http://www.gnuplot.info/) or used with [pgfplots](https://mirror.easyname.at/ctan/graphics/pgf/contrib/pgfplots/doc/pgfplots.pdf). The two graphs at the top of this file, for example, were generated using the gnuplot scripts in the `examples/plots` folder, using data in `examples/data`.

## Sorters

Sorters are functions with the signature `void(I first, I last, P cmp = P{})` where `I` models an Iterator and `P` models a Predicate (defaults to `std::less<>`).

Currently, relatively basic versions of the insertion sort, quick sort, heap sort and merge sort are implemented.

These implementations _aren't_ excessively optimized for any metric. This means that there are certainly faster versions of these algorithms around. They do however rely strongly on the STL, which is (usually) heavily optimized and thoroughly tested. This is done primarily to avoid any kind of bias in the development, since one might be tempted to optimize one algorithm more than another when writing them from scratch. It also allows for the implementations to be concise as well as easy to read and understand which are arguably some of the most important properties of any code.

## Sets

Datasets are of type `std::vector<int>`.

The most basic set type is `sorted`, which is simply initialized with `std::iota(first, last, 1)`, resulting in a set with the contents `1, 2, 3, ..., n` where `n` is the set size.

Other set types are a permutation of this, namely

- `random`: a `std::shuffle`d version of `sorted`
- `inverted`: an inverted version of `sorted` (`n, ..., 3, 2, 1`)

## Step Types

As was established earlier, running `benchmark -o example/data` generates a number of files which contain data arranged into rows of the format `[chunk size] [time]`.

By default, these chunk sizes increase linearly in value, meaning chunk sizes increase by a constant value for every row; the step size is constant and thus a linear step type is used. 

In this case, the step size can easily be calculated through
```
chunk_size = set_size / total_chunks
```
where `set_size` is `-s` and `total_chunks` is `-c`. For the current defaults this results in `chunk_size = 2^18 / 128 = 2048`, meaning that the first chunk has a size of 2048, the second a size of 4096 and so forth. (The `i`th chunk can thus be calculated through `(set_size / total_chunks) * i`.)

An alternative to this linear generation is the quadratic step type which can be enabled through `-t quadratic`. Assume that `f(i)` is a function of the form `f(i) = ai^2` modeling the chunk sizes for the chunk indices `ì in [1, total_chunks]`.

```
f(i) = a * i^2
f(total_chunks) = set_size = a * total_chunks^2
a = set_size / total_chunks^2
```

Thus, the size of the `i`th chunk can be calculated through `(set size / total_chunks^2) * i^2`.

<p float="middle">
  <img src="https://github.com/fs-c/sorting-efficiency/blob/master/example/steps/step_types.png" width="390" />
  <img src="https://github.com/fs-c/sorting-efficiency/blob/master/example/steps/small_step_types.png" width="390" /> 
</p>

You can see two graphs of the chunk sizes for a total set size of 2^18, divided into 128 chunks (the default value) with the linear and quadratic step types.

## Building

Make sure that you have a C++17 conformant compiler and CMake installed.

```
git clone https://github.com/LW2904/sorting-efficiency.git
# the folder name is merely a suggestion
mkdir build && cd build
cmake ..
# to build all targets
make
# to run unit tests
make test
```

You will find an executable named `benchmark` in the `build` folder.

I've previously been able to compile and run on

- Arch Linux and Ubuntu with GCC 10.1.0 and CMake 3.17.3
- Windows 10 (1903) with cl 19.22.27905 and CMake 3.16.5

### CI

![CI build](https://github.com/fs-c/sorting-efficiency/actions/workflows/build-on-push.yml/badge.svg)

There's a CI build job which runs on every push, builds are generated for Linux and available for download as build artifacts. (Switch to the Actions tab and select a workflow run, you'll see a `build` artifact in the Artifacts pane.)


