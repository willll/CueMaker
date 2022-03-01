//
// Created by will on 2022-02-25.
//

#ifndef CUEMAKER_GENERATE_CUE_H
#define CUEMAKER_GENERATE_CUE_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include <plog/Log.h>
#include <inja.hpp>

#include "cli_options.h"
#include "template.h"

namespace fs = boost::filesystem;


bool find_file(const fs::path& dir_path, fs::path& file_found) {
    const fs::directory_iterator end;
    const fs::path ext_iso = ".iso";
    const auto it = find_if(fs::directory_iterator(dir_path), end,
                            [&ext_iso](const fs::directory_entry& e) {
                                return e.path().filename().extension() == ext_iso;
                            });
    if (it == end) {
        return false;
    } else {
        file_found = it->path();
        return true;
    }
}

bool parse_directory(const fs::path & inputfolder, inja::json & dict) {
    bool bReturn = false;
    fs::path file_found;

    if(find_file(inputfolder, file_found)) {
        dict["ISO"] = file_found.filename().c_str();
        bReturn = true;
    }

    return bReturn;
}

void generate_cue(const CliOptions & options) {

    inja::json dict;
    std::string output;

    if (parse_directory(options.inputfolder, dict)) {
        output = inja::render(template_cue, dict);
        PLOG_VERBOSE_IF(options.verbose) << output;
        fs::ofstream ofs(options.outputfile);
        ofs << output;
        ofs.close();
        PLOG_VERBOSE_IF(options.verbose) << "Written into : " << options.outputfile;
    } else {
        PLOG_FATAL << "No ISO file found in : "
                   << options.inputfolder
                   << "\n";
    }
}

#endif //CUEMAKER_GENERATE_CUE_H
