#ifndef DIRC_CONFIG_DOC_BUILDER_H
#define DIRC_CONFIG_DOC_BUILDER_H

#include <core/dirc_config.h>
#include <config/xml_document.h>

namespace config {

class DircConfigDocBuilder {
public:
    DircConfigDocBuilder(core::DircConfig &config, xml::Document &document);
    void build();
private:
    void build_global_user_info(xml::Element &root);
    void build_nicknames(std::vector<std::string> &nicknames, xml::Element &root);
    void build_networks(std::vector<core::Network> &networks, xml::Element &root);
    void build_network(core::Network &network, xml::Element &root);
    void build_servers(std::vector<core::Server> &servers, xml::Element &root);
    void build_server(core::Server &server, xml::Element &root);
    void build_channels(std::vector<core::Channel> &channels, xml::Element &root);
    void build_channel(core::Channel &channel, xml::Element &root);
    void build_commands(std::vector<std::string> &commands, xml::Element &root);
    void build_user_info(core::Network &network, xml::Element &root);

    core::DircConfig &m_config;
    xml::Document &m_document;
};

}

#endif // DIRC_CONFIG_DOC_BUILDER_H
