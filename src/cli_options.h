//
// Created by will on 2022-02-24.
//

#ifndef CUEMAKER_CLI_OPTIONS_H
#define CUEMAKER_CLI_OPTIONS_H

#include <filesystem>

struct CliOptions{
    std::filesystem::path outputfile;
    std::filesystem::path inputfolder;
    bool verbose = false;
};

#endif //CUEMAKER_CLI_OPTIONS_H
