#pragma once

#include "job.h"
#include "benchmark.h"
#include "deps/argh.h"

class config {
	argh::parser cmd;

	static void print_help();

	void parse(char *argv[]);

	void verify();

public:
	std::string output = "./out";

	size_t sample_size = 512 * 512;

	size_t total_chunks = 128;

	benchmark::step_type step_type = benchmark::step_type::linear;

	size_t runs = 1;
	job::reduction_type reduction_type = job::reduction_type::none;

	bool randomize_execution = false;

	bool write_run_info = false;

	bool should_exit = false;

	config();
	explicit config(char *argv[]);
};
