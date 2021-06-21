#pragma once

#include "benchmark.h"
#include "deps/argh.h"

class config {
	argh::parser cmd;

	static void print_help();

	void parse(char *argv[]);

	size_t average = 0, median = 0;

	void verify();

public:
	std::string output = "./out";

	size_t sample_size = 512 * 512;

	size_t total_chunks = 128;

	benchmark::step_type_t step_type = benchmark::step_type_t::linear;

	size_t runs = 1;
	benchmark::result_group::reduction_type reduction_type =
		benchmark::result_group::reduction_type::none;

	bool randomize_execution = false;

	bool should_exit = false;

	config();
	explicit config(char *argv[]);
};
