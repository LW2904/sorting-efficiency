#pragma once

#include "deps/argh.h"
#include "benchmark.h"

class config {
	argh::parser cmd;

	static void print_help();

	void parse(char *argv[]);

	void verify();

public:
	std::string output = "./out";

	size_t sample_size = 512 * 512;

	size_t total_chunks = 128;

	benchmark::step_type step_type = benchmark::linear;

	size_t average = 0;

	size_t median = 0;

	bool randomize_tasks = false;

	bool write_run_info = false;

	bool should_exit = false;

	config();
	explicit config(char *argv[]);
};
