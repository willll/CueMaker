//
// Created by will on 2022-02-24.
//

#include "cli_parser.h"
#include "fssanity.h"
#include "generate_cue.h"

int main(int ac, char* av[]) {
    CliOptions options;

    // parse command line
    ParseCli(ac, av, options);

    // sanity checks
    if (!valid_path(options)) {
        return 1;
    }

    // generate
    generate_cue(options);

    return 0;
}