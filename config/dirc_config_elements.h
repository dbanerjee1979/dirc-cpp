#ifndef DIRC_CONFIG_ELEMENTS_H
#define DIRC_CONFIG_ELEMENTS_H

#include <string>

namespace config {

struct DircConfigElement {
    static const std::string global_user_info;
    static const std::string networks;
    static const std::string network;
    static const std::string show_favorites_only;
    static const std::string skip_network_list_on_startup;
    static const std::string nicknames;
    static const std::string nickname;
    static const std::string username;
    static const std::string realname;
    static const std::string name;
    static const std::string favorite;
    static const std::string servers;
    static const std::string server;
    static const std::string auto_join_channels;
    static const std::string channel;
    static const std::string connect_commands;
    static const std::string command;
    static const std::string connect_selected_server_only;
    static const std::string connect_automatically;
    static const std::string bypass_proxy;
    static const std::string use_ssl;
    static const std::string accept_invalid_ssl_cert;
    static const std::string use_global_user_info;
    static const std::string user_info;
    static const std::string login_method;
    static const std::string password;
    static const std::string charset;
    static const std::string hostname;
    static const std::string port;
    static const std::string selected;
    static const std::string key;
};

}

#endif // DIRC_CONFIG_ELEMENTS_H
