//
// Created by will on 2022-02-24.
//

#ifndef CUEMAKER_CLI_PARSER_H
#define CUEMAKER_CLI_PARSER_H

#include <iostream>
#include <exception>
#include <string>

#include <boost/program_options.hpp>
#include <plog/Log.h>

#include "cli_options.h"

namespace po = boost::program_options;
using namespace std;

void help(const po::options_description &desc) {
    cout << desc << "\n";
}

void ParseCli(int ac, char* av[], CliOptions & options) {

    po::options_description desc("Allowed options");
    try {
        desc.add_options()
                ("help,h", "This output")
                ("verbose,v", "Verbose")
                ("output,o", po::value<string>(), "output cue file")
                ("path,p", po::value<string>()->default_value("."), "path to generate the cue file from, default is current path");

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            help(desc);
            exit(0);
        }

        if (vm.count("verbose")) {
            options.verbose = true;
        }

        if (vm.count("output")) {
            options.outputfile = vm["output"].as<string>();
            PLOG_VERBOSE_IF(options.verbose) << "Output file :"
                                            <<  options.outputfile << ".\n";
        } else {
            PLOG_FATAL << "Output file is missing\n";
            help(desc);
            exit(1);
        }

        if (vm.count("path")) {
            options.inputfolder = vm["path"].as<string>();
            PLOG_VERBOSE_IF(options.verbose) << "Input Folder :"
                                            <<  options.inputfolder << ".\n";
        }
    }
    catch(exception& e) {
        PLOG_FATAL << "error: " << e.what() << "\n";
        help(desc);
        exit(1);
    }
    catch(...) {
        PLOG_FATAL << "Exception of unknown type!\n";
        help(desc);
        exit(1);
    }
}

#endif //CUEMAKER_CLI_PARSER_H
