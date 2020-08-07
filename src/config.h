#include "deps/argh.h"

class config {
	argh::parser cmd;

	void print_help() {
		printf(
"Usage: sorting [options]\n"
"Options:\n"
"  -h, --help        Display this information and exit.\n"
"  -s, --strategy    Sets the benchmarking strategy. Valid parameters are \"human\"\n"
"                    and \"gnuplot\". Currently, only the latter is supported.\n"
"  -o, --output      Sets the output path if the strategy is set to \"gnuplot\".\n"
		);
	}

	void parse() {
		if (cmd[{ "h", "help" }]) {
			should_exit = true;
			return print_help();
		}

		std::string _strategy;
		cmd("strategy") >> _strategy;
		if (_strategy == "human") {
			strategy = strategy::human;
		} else if (_strategy == "gnuplot") {
			strategy = strategy::gnuplot;
		}

		cmd("output") >> output;
	}

public:
	enum class strategy { human, gnuplot };
	strategy strategy = strategy::human;

	std::string output = "out/";

	bool should_exit = false;

	config(char *argv[]) : cmd(argh::parser(argv)) {
		parse();
	};
};
