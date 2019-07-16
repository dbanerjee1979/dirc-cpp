#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>
#include "dirc_config_elements.h"
#include "dirc_config_builder.h"

namespace config {

DircConfigBuilder::DircConfigBuilder(
            xml::Document &document,
            core::LoginMethodFactory &login_method_factory,
            core::CharsetFactory &charset_factory) :
        m_document(document),
        m_login_method_factory(login_method_factory),
        m_charset_factory(charset_factory) {
}

core::DircConfig DircConfigBuilder::build() {
    core::DircConfig config;
    m_document.get_root().for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::global_user_info)) {
            build_global_user_info(config, child);
        }
        else if (boost::iequals(name, DircConfigElement::networks)) {
            build_networks(config.networks, child);
        }
        else if (boost::iequals(name, DircConfigElement::skip_network_list_on_startup)) {
            config.skip_list_on_startup = child.get_bool();
        }
        else if (boost::iequals(name, DircConfigElement::show_favorites_only)) {
            config.show_favorites = child.get_bool();
        }
    });
    return config;
}

void DircConfigBuilder::build_global_user_info(core::DircConfig &conf, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::nicknames)) {
            build_nicknames(conf.nicknames, child);
        }
        else if (boost::iequals(name, DircConfigElement::username)) {
            conf.username = boost::trim_copy(child.get_text());
        }
    });
}

void DircConfigBuilder::build_nicknames(std::vector<std::string> &nicknames, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::nickname)) {
            nicknames.push_back(boost::trim_copy(child.get_text()));
        }
    });
}

void DircConfigBuilder::build_networks(std::vector<core::Network> &networks, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::network)) {
            networks.push_back(core::Network());
            build_network(networks.back(), child);
        }
    });
}

void DircConfigBuilder::build_network(core::Network &network, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::name)) {
            network.name = boost::trim_copy(child.get_text());
        }
        else if (boost::iequals(name, DircConfigElement::favorite)) {
            network.favorite = child.get_bool();
        }
        else if (boost::iequals(name, DircConfigElement::servers)) {
            build_servers(network.servers, child);
        }
        else if (boost::iequals(name, DircConfigElement::auto_join_channels)) {
            build_channels(network.autojoin_channels, child);
        }
        else if (boost::iequals(name, DircConfigElement::connect_commands)) {
            build_commands(network.connect_commands, child);
        }
        else if (boost::iequals(name, DircConfigElement::connect_selected_server_only)) {
            network.connect_selected_server_only = child.get_bool();
        }
        else if (boost::iequals(name, DircConfigElement::connect_automatically)) {
            network.connect_automatically = child.get_bool();
        }
        else if (boost::iequals(name, DircConfigElement::bypass_proxy)) {
            network.bypass_proxy = child.get_bool();
        }
        else if (boost::iequals(name, DircConfigElement::use_ssl)) {
            network.use_ssl = child.get_bool();
        }
        else if (boost::iequals(name, DircConfigElement::accept_invalid_ssl_cert)) {
            network.accept_invalid_ssl_cert = child.get_bool();
        }
        else if (boost::iequals(name, DircConfigElement::use_global_user_info)) {
            network.use_global_user_info = child.get_bool();
        }
        else if (boost::iequals(name, DircConfigElement::user_info)) {
            build_user_info(network, child);
        }
        else if (boost::iequals(name, DircConfigElement::login_method)) {
            network.login_method = build_login_method(child);
        }
        else if (boost::iequals(name, DircConfigElement::password)) {
            network.password = boost::trim_copy(name);
        }
        else if (boost::iequals(name, DircConfigElement::charset)) {
            network.charset = build_charset(child);
        }
    });
}

void DircConfigBuilder::build_servers(std::vector<core::Server> &servers, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::server)) {
            servers.push_back(core::Server());
            build_server(servers.back(), child);
        }
    });
}

void DircConfigBuilder::build_server(core::Server &server, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::hostname)) {
            server.hostname = boost::trim_copy(child.get_text());
        }
        else if (boost::iequals(name, DircConfigElement::port)) {
            std::string port = boost::trim_copy(child.get_text());
            server.port = port.empty() ? 0 : std::stoul(port);
        }
        else if (boost::iequals(name, DircConfigElement::selected)) {
            server.selected = child.get_bool();
        }
    });
}

void DircConfigBuilder::build_channels(std::vector<core::Channel> &channels, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::channel)) {
            channels.push_back(core::Channel());
            build_channel(channels.back(), child);
        }
    });
}

void DircConfigBuilder::build_channel(core::Channel &channel, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::name)) {
            channel.name = boost::trim_copy(child.get_text());
        }
        else if (boost::iequals(name, DircConfigElement::key)) {
            channel.key = boost::trim_copy(child.get_text());
        }
    });
}

void DircConfigBuilder::build_commands(std::vector<std::string> &commands, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::command)) {
            commands.push_back(boost::trim_copy(child.get_text()));
        }
    });
}

void DircConfigBuilder::build_user_info(core::Network &network, const xml::Element &root) {
    root.for_each([&] (const xml::Element &child) {
        auto name = child.get_name();
        if (boost::iequals(name, DircConfigElement::nicknames)) {
            build_nicknames(network.nicknames, root);
        }
        else if (boost::iequals(name, DircConfigElement::realname)) {
            network.realname = boost::trim_copy(child.get_text());
        }
        else if (boost::iequals(name, DircConfigElement::username)) {
            network.username = boost::trim_copy(child.get_text());
        }
    });
}

std::string DircConfigBuilder::build_login_method(const xml::Element &child) {
    std::string s_login_method = boost::trim_copy(child.get_text());
    boost::optional<core::LoginMethod &> login_method;
    if (s_login_method.empty() || !(login_method = m_login_method_factory.find_login_method(s_login_method))) {
        return m_login_method_factory.get_default_method();
    }
    else {
        return s_login_method;
    }
}

std::string DircConfigBuilder::build_charset(const xml::Element &child) {
    std::string s_charset = boost::trim_copy(child.get_text());
    boost::optional<core::LoginMethod &> login_method;
    if (s_charset.empty() || !(login_method = m_login_method_factory.find_login_method(s_charset))) {
        return m_login_method_factory.get_default_method();
    }
    else {
        return s_charset;
    }
}

}
