#include "config.h"

void config::print_help() {
	printf(
		"Usage: benchmark [options]\n"
		"Options:\n"
		"  -h, --help        Display this information and exit.\n"
		"  -o, --output      Sets the output path. (default: ./out)\n"
		"  -s, --size        Sets the sample size. (default: 262144 i.e. 2^18)\n"
		"  -c, --chunks      Sets the number of chunks that the set will be devided into.\n"
		"                    (default: 128)\n"
		"  -t, --step-type   Specifies the step type to use, one of 'linear' or\n"
		"                    'quadratic'. (default: linear)\n"
		"  -a, --average     Repeat the benchmarking a given number of times and output\n"
		"                    the average results of all runs. (default: 0)\n"
		"  -m, --median      Like -a, except it outputs the median. (default: 0)\n"
		"  -r, --randomize   Randomize the order in which the different combinations\n"
		"                    between sorters and sets are benchmarked. (default: false)\n"
		"  -i, --run-info    Output an additional file with meta information about the\n"
		"                    current run. (default: false)\n"
	);
}

void config::parse(char *argv[]) {
	cmd.parse(argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

	if (cmd[{"h", "help"}]) {
		should_exit = true;
		return print_help();
	}

	cmd({"output", "o"}) >> output;

	cmd({"size", "s"}) >> sample_size;

	cmd({"chunks", "c"}) >> total_chunks;

	std::string _step_type;
	cmd({"step-type", "t"}) >> _step_type;

	if (_step_type == "linear") {
		step_type = benchmark::linear;
	} else if (_step_type == "quadratic") {
		step_type = benchmark::quadratic;
	}

	cmd({"average", "a"}) >> average;

	cmd({"median", "m"}) >> median;

	randomize_tasks = cmd[{"randomize", "r"}];

	write_run_info = cmd[{"run-info", "i"}];
}

void config::verify() {
	if (this->total_chunks > this->sample_size) {
		printf("error: the number of subsets to be generated (%zu) "
		       "is larger than the sample size (%zu)\n", this->total_chunks,
			this->sample_size);

		this->should_exit = true;
	}

	if (this->average && this->median) {
		printf("error: average and median cannot be used together\n");

		this->should_exit = true;
	}
}

config::config(char *argv[]) {
	parse(argv);

	verify();
}

config::config() = default;
