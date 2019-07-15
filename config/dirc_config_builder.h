#ifndef DIRC_CONFIG_BUILDER_H
#define DIRC_CONFIG_BUILDER_H

#include <string>
#include <vector>
#include <core/dirc_config.h>
#include <core/login_method_factory.h>
#include <core/charset_factory.h>
#include "xml_document.h"

namespace config {

class DircConfigBuilder {
public:
    DircConfigBuilder(
            xml::Document &document,
            core::LoginMethodFactory &login_method_factory,
            core::CharsetFactory &charset_factory);
    core::DircConfig build();
private:
    void build_global_user_info(core::DircConfig &conf, const xml::Element &root);
    void build_nicknames(std::vector<std::string> &nicknames, const xml::Element &root);
    void build_networks(std::vector<core::Network> &networks, const xml::Element &root);
    void build_network(core::Network &network, const xml::Element &root);
    void build_servers(std::vector<core::Server> &servers, const xml::Element &root);
    void build_server(core::Server &server, const xml::Element &root);
    void build_channels(std::vector<core::Channel> &channels, const xml::Element &root);
    void build_channel(core::Channel &channel, const xml::Element &root);
    void build_commands(std::vector<std::string> &commands, const xml::Element &root);
    void build_user_info(core::Network &network, const xml::Element &root);
    std::string build_login_method(const xml::Element &child);
    std::string build_charset(const xml::Element &child);

    xml::Document &m_document;
    core::LoginMethodFactory &m_login_method_factory;
    core::CharsetFactory &m_charset_factory;
};

}

#endif // DIRC_CONFIG_BUILDER_H
