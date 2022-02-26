//
// Created by will on 2022-02-24.
//

#ifndef CUEMAKER_CLI_PARSER_H
#define CUEMAKER_CLI_PARSER_H

#include <iostream>
#include <exception>
#include <string>

#include <boost/program_options.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include "cli_options.h"

namespace po = boost::program_options;
using namespace std;

void help(const po::options_description &desc) {
    cout << desc << "\n";
}

void ParseCli(int ac, char* av[], CliOptions & options) {

    try {
        po::options_description desc("Allowed options");
        desc.add_options()
                ("help,h", "This output")
                ("verbose,v", "Verbose")
                ("output,o", po::value<string>(), "output cue file")
                ("path,p,d", po::value<string>()->default_value("."), "path to generate the cue file from, default is current path");

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
            cout << "Output file :"
                 <<  options.outputfile << ".\n";
        } else {
            cerr << "Output file is missing\n";
            help(desc);
            exit(1);
        }

        if (vm.count("path")) {
            options.inputfolder = vm["path"].as<string>();
            cout << "Input Folder :"
                 <<  options.inputfolder << ".\n";
        }
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        exit(1);
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
        exit(1);
    }
}

#endif //CUEMAKER_CLI_PARSER_H
