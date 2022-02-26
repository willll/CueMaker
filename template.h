//
// Created by will on 2022-02-26.
//

#ifndef CUEMAKER_TEMPLATE_H
#define CUEMAKER_TEMPLATE_H

static const char template_cue[] =
        "FILE \"{{ISO}}\" BINARY\n"
        "\tTRACK 01 MODE1/2048\n"
        "\t\tINDEX 01 00:00:00\n"
        "\t\tPOSTGAP 00:02:00\n";

#endif //CUEMAKER_TEMPLATE_H
