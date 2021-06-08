#pragma once

#include "deps/argh.h"
#include "benchmark.h"

class config {
	argh::parser cmd;

	static void print_help();

	void parse(char *argv[]);

public:
	std::string output = "./out";

	size_t sample_size = 512 * 512;

	size_t total_chunks = 128;

	benchmark::step_type_t step_type = benchmark::linear;

	bool should_exit = false;

	explicit config(char *argv[]);
};
