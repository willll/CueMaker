//
// Created by will on 2022-02-25.
//

#ifndef CUEMAKER_GENERATE_CUE_H
#define CUEMAKER_GENERATE_CUE_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include <ctemplate/template.h>

#include "cli_options.h"
#include "template.h"

namespace fs = boost::filesystem;
namespace ct = ctemplate;

bool find_file(const fs::path& dir_path, fs::path& file_found) {
    const fs::directory_iterator end;
    const fs::path ext = ".iso";
    const auto it = find_if(fs::directory_iterator(dir_path), end,
                            [&ext](const fs::directory_entry& e) {
                                return e.path().filename().extension() == ext;
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

    ctemplate::StringToTemplateCache("cue_template", template_cue, ctemplate::DO_NOT_STRIP);

    parse_directory(options.inputfolder, dict);

    ctemplate::ExpandTemplate("cue_template", ctemplate::DO_NOT_STRIP, &dict, &output);

    std::cout << output;
}

#endif //CUEMAKER_GENERATE_CUE_H
