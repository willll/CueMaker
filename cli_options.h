//
// Created by will on 2022-02-24.
//

#ifndef CUEMAKER_CLI_OPTIONS_H
#define CUEMAKER_CLI_OPTIONS_H

#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;

struct CliOptions{
    fs::path outputfile;
    fs::path inputfolder;
    bool verbose = false;
};

#endif //CUEMAKER_CLI_OPTIONS_H
