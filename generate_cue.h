//
// Created by will on 2022-02-25.
//

#ifndef CUEMAKER_GENERATE_CUE_H
#define CUEMAKER_GENERATE_CUE_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <ctemplate/template.h>
#include <plog/Log.h>

#include "cli_options.h"
#include "template.h"

namespace fs = boost::filesystem;
namespace ct = ctemplate;

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

bool parse_directory(const fs::path & inputfolder, ct::TemplateDictionary & dict) {
    bool bReturn = false;
    fs::path file_found;

    if(find_file(inputfolder, file_found)) {
        dict["ISO"] = file_found.filename().c_str();
        bReturn = true;
    }

    return bReturn;
}

void generate_cue(const CliOptions & options) {

    ct::TemplateDictionary dict("cue_file");
    std::string output;

    ct::StringToTemplateCache("cue_template", template_cue, ctemplate::DO_NOT_STRIP);

    if (parse_directory(options.inputfolder, dict)) {
        ct::ExpandTemplate("cue_template", ct::DO_NOT_STRIP, &dict, &output);
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
