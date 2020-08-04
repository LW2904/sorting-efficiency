#include "deps/argh.h"

class config {
	argh::parser cmd;

	void print_help() {
		printf(
"Usage: sorting [options]\n"
"Options:\n"
"  -h, --help        Display this information and exit.\n"
"  -o, --output      Sets the output type, accepted values are 'human' and"
"                    'gnuplot'."
		);
	}

	void parse() {
		if (cmd[{ "h", "help" }]) {
			return print_help();
		}

		std::string _output;
		cmd("output") >> _output;
		if (_output == "human") {
			output = output::human;
		} else if (_output == "gnuplot") {
			output = output::gnuplot;
		}
	}

public:
	enum class output { human, gnuplot };
	output output = output::human;

	config(char *argv[]) : cmd(argh::parser(argv)) {
		parse();
	};
};
