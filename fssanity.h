//
// Created by will on 2022-02-24.
//

#ifndef CUEMAKER_FSSANITY_H
#define CUEMAKER_FSSANITY_H

#include <iostream>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <plog/Log.h>

#include "cli_options.h"

namespace fs = boost::filesystem;
using namespace std;

bool valid_path(const CliOptions & options) {
    if (options.inputfolder.compare(".")) {
        if (!fs::exists(options.inputfolder)) {
            PLOG_FATAL << "Input path does not exist : "
                << options.inputfolder
                << "\n";
            return false;
        }

        if (fs::exists(options.outputfile)) {
            PLOG_FATAL << "Output file already exists : "
                 << options.outputfile
                 << "\n";
            return false;
        }

        try {
            fs::wofstream ofs(options.outputfile);
            ofs.close();
        }
        catch(exception& e) {
            PLOG_FATAL << "error: " << e.what() << "\n";
            return false;
        }
        catch(...) {
            PLOG_FATAL << "Exception of unknown type!\n";
            return false;
        }
    }
    return true;
}

#endif //CUEMAKER_FSSANITY_H
