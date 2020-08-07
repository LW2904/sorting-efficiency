#include "deps/argh.h"

class config {
	argh::parser cmd;

	void print_help() {
		printf(
"Usage: sorting [options]\n"
"Options:\n"
"  -h, --help        Display this information and exit.\n"
"  -o, --output      Sets the output path, relative to the current working directory.\n"
		);
	}

	void parse() {
		if (cmd[{ "h", "help" }]) {
			should_exit = true;
			return print_help();
		}

		cmd("output") >> output;
	}

public:
	std::string output = "out/";

	bool should_exit = false;

	config(char *argv[]) : cmd(argh::parser(argv)) {
		parse();
	};
};
