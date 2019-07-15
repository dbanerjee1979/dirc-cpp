#include "dirc_config_doc_builder.h"
#include "dirc_config_elements.h"

using std::placeholders::_1;

namespace config {

DircConfigDocBuilder::DircConfigDocBuilder(
            core::DircConfig &config,
            xml::Document &document) :
        m_config(config),
        m_document(document) {
}

void DircConfigDocBuilder::build() {
    xml::Element root = m_document.get_root();
    root.append_child(DircConfigElement::global_user_info, [&] (xml::Element &child) {
        build_global_user_info(child);
    });
    root.append_child(DircConfigElement::networks, [&] (xml::Element &child) {
        build_networks(m_config.networks, child);
    });
    root.append_child(DircConfigElement::skip_network_list_on_startup, [&] (xml::Element &child) {
        child.set_bool(m_config.skip_list_on_startup);
    });
    root.append_child(DircConfigElement::show_favorites_only, [&] (xml::Element &child) {
        child.set_bool(m_config.show_favorites);
    });
}

void DircConfigDocBuilder::build_global_user_info(xml::Element &root) {
    root.append_child(DircConfigElement::nicknames, [&] (xml::Element &child) {
        build_nicknames(m_config.nicknames, child);
    });
    root.append_child(DircConfigElement::username, [&] (xml::Element &child) {
        child.set_text(m_config.username);
    });
}

void DircConfigDocBuilder::build_nicknames(std::vector<std::string> &nicknames, xml::Element &root) {
    for (auto it = nicknames.begin(); it != nicknames.end(); it++) {
        root.append_child(DircConfigElement::nickname, [&] (xml::Element &child) {
            child.set_text(*it);
        });
    }
}

void DircConfigDocBuilder::build_networks(std::vector<core::Network> &networks, xml::Element &root) {
    for (auto it = networks.begin(); it != networks.end(); it++) {
        root.append_child(DircConfigElement::network, [&] (xml::Element &child) {
            build_network(*it, child);
        });
    }
}

void DircConfigDocBuilder::build_network(core::Network &network, xml::Element &root) {
    root.append_child(DircConfigElement::name, [&] (xml::Element &child) {
        child.set_text(network.name);
    });
    root.append_child(DircConfigElement::favorite, [&] (xml::Element &child) {
        child.set_bool(network.favorite);
    });
    root.append_child(DircConfigElement::servers, [&] (xml::Element &child) {
        build_servers(network.servers, child);
    });
    root.append_child(DircConfigElement::auto_join_channels, [&] (xml::Element &child) {
        build_channels(network.autojoin_channels, child);
    });
    root.append_child(DircConfigElement::connect_commands, [&] (xml::Element &child) {
        build_commands(network.connect_commands, child);
    });
    root.append_child(DircConfigElement::connect_selected_server_only, [&] (xml::Element &child) {
        child.set_bool(network.connect_selected_server_only);
    });
    root.append_child(DircConfigElement::connect_automatically, [&] (xml::Element &child) {
        child.set_bool(network.connect_automatically);
    });
    root.append_child(DircConfigElement::bypass_proxy, [&] (xml::Element &child) {
        child.set_bool(network.bypass_proxy);
    });
    root.append_child(DircConfigElement::use_ssl, [&] (xml::Element &child) {
        child.set_bool(network.use_ssl);
    });
    root.append_child(DircConfigElement::accept_invalid_ssl_cert, [&] (xml::Element &child) {
        child.set_bool(network.accept_invalid_ssl_cert);
    });
    root.append_child(DircConfigElement::use_global_user_info, [&] (xml::Element &child) {
        child.set_bool(network.use_global_user_info);
    });
    root.append_child(DircConfigElement::user_info, [&] (xml::Element &child) {
        build_user_info(network, child);
    });
    root.append_child(DircConfigElement::login_method, [&] (xml::Element &child) {
        child.set_text(network.login_method);
    });
    root.append_child(DircConfigElement::password, [&] (xml::Element &child) {
        child.set_text(network.password);
    });
    root.append_child(DircConfigElement::charset, [&] (xml::Element &child) {
        child.set_text(network.charset);
    });
}

void DircConfigDocBuilder::build_servers(std::vector<core::Server> &servers, xml::Element &root) {
    for (auto it = servers.begin(); it != servers.end(); it++) {
        root.append_child(DircConfigElement::server, [&] (xml::Element &child) {
            build_server(*it, child);
        });
    }
}

void DircConfigDocBuilder::build_server(core::Server &server, xml::Element &root) {
    root.append_child(DircConfigElement::hostname, [&] (xml::Element &child) {
        child.set_text(server.hostname);
    });
    if (server.port > 0) {
        root.append_child(DircConfigElement::port, [&] (xml::Element &child) {
            child.set_text(std::to_string(server.port));
        });
    }
    root.append_child(DircConfigElement::selected, [&] (xml::Element &child) {
        child.set_bool(server.selected);
    });
}

void DircConfigDocBuilder::build_channels(std::vector<core::Channel> &channels, xml::Element &root) {
    for (auto it = channels.begin(); it != channels.end(); it++) {
        root.append_child(DircConfigElement::channel, [&] (xml::Element &child) {
            build_channel(*it, child);
        });
    }
}

void DircConfigDocBuilder::build_channel(core::Channel &channel, xml::Element &root) {
    root.append_child(DircConfigElement::name, [&] (xml::Element &child) {
        child.set_text(channel.name);
    });
    root.append_child(DircConfigElement::key, [&] (xml::Element &child) {
        child.set_text(channel.key);
    });
}

void DircConfigDocBuilder::build_commands(std::vector<std::string> &commands, xml::Element &root) {
    for (auto it = commands.begin(); it != commands.end(); it++) {
        root.append_child(DircConfigElement::command, [&] (xml::Element &child) {
            child.set_text(*it);
        });
    }
}

void DircConfigDocBuilder::build_user_info(core::Network &network, xml::Element &root) {
    root.append_child(DircConfigElement::nicknames, [&] (xml::Element &child) {
        build_nicknames(network.nicknames, child);
    });
    root.append_child(DircConfigElement::realname, [&] (xml::Element &child) {
        child.set_text(network.realname);
    });
    root.append_child(DircConfigElement::username, [&] (xml::Element &child) {
        child.set_text(network.username);
    });
}

}
