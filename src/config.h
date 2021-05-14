#pragma once

#include "deps/argh.h"
#include "benchmark.h"

class config {
	argh::parser cmd;

	void print_help() {
		printf(
"Usage: sorting [options]\n"
"Options:\n"
"  -h, --help        Display this information and exit.\n"
"  -o, --output      Sets the output path. (default: ./out)\n"
"  -s, --size        Sets the sample size. (default: 262144 i.e. 512^2)\n"
"  -c, --chunks      Sets the number of chunks that the set will be devided into.\n"
"                    (default: 128)\n"
"  -g, --generator   Specifies the step generator to use, one of 'linear' or\n"
"                    'quadratic'. (default: quadratic)"
		);
	}

	void parse(char *argv[]) {
		cmd.parse(argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

		if (cmd[{ "h", "help" }]) {
			should_exit = true;
			return print_help();
		}

		cmd({ "output", "o" }) >> output;

		cmd({ "size", "s" }) >> sample_size;

		cmd({ "chunks", "c" }) >> total_chunks;

		std::string _step_generator;
		cmd({ "generator", "g" }) >> _step_generator;

		if (!_step_generator.compare("linear")) {
			step_generator = benchmark::linear;
		} else if (!_step_generator.compare("quadratic")) {
			step_generator = benchmark::quadratic;
		}
	}

public:
	std::string output = "./out";
	size_t sample_size = 512 * 512;
	int total_chunks = 128;
	benchmark::step_generator_t step_generator = benchmark::quadratic;

	bool should_exit = false;

	config(char *argv[]) {
		parse(argv);
	};
};
