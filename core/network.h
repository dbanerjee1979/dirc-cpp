#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>
#include "server.h"
#include "channel.h"

namespace core {

struct Network {
    std::string name;
    bool favorite;
    std::vector<Server> servers;
    std::vector<Channel> autojoin_channels;
    std::vector<std::string> connect_commands;
    bool connect_selected_server_only;
    bool connect_automatically;
    bool bypass_proxy;
    bool use_ssl;
    bool accept_invalid_ssl_cert;
    bool use_global_user_info;
    std::vector<std::string> nicknames;
    std::string realname;
    std::string username;
    std::string login_method;
    std::string password;
    std::string charset;

    Network() :
        favorite(false),
        connect_selected_server_only(false),
        connect_automatically(false),
        bypass_proxy(false),
        use_ssl(false),
        accept_invalid_ssl_cert(false),
        use_global_user_info(false) {
    }
};

}

#endif // NETWORK_H
