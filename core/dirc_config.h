#ifndef DIRC_CONFIG_H
#define DIRC_CONFIG_H

#include <vector>
#include <string>
#include "network.h"

namespace core {

struct DircConfig {
    std::vector<std::string> nicknames;
    std::string username;
    std::vector<Network> networks;
    bool show_favorites;
    bool skip_list_on_startup;

    DircConfig() :
        show_favorites(false),
        skip_list_on_startup(false) {
    }
};

}

#endif // DIRC_CONFIG_H
