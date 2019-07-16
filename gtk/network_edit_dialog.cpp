#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include "network_edit_dialog.h"
#include "network_list_dialog.h"

namespace gtk {

ServerColumns::ServerColumns() {
    add(m_selected);
    add(m_server);
}

ChannelColumns::ChannelColumns() {
    add(m_name);
    add(m_password);
}

CommandColumns::CommandColumns() {
    add(m_command);
}

NetworkEditDialog::NetworkEditDialog() :
        m_closing(false),
        m_server_pattern("\\s*((?:[A-z0-9-]+\\.)*[A-z0-9-]+)(?:/([0-9]*))?\\s*"),
        m_servers_model(Gtk::ListStore::create(m_server_columns)),
        m_channels_model(Gtk::ListStore::create(m_channel_columns)),
        m_commands_model(Gtk::ListStore::create(m_command_columns)),
        m_server_lbl("Servers"),
        m_autojoin_lbl("Autojoin Channels"),
        m_connect_cmds_lbl("Connect Commands"),
        m_add_btn("Add"),
        m_del_btn("Remove"),
        m_selected_server_only("Connect to selected server only"),
        m_auto_conn_network("Connect to this network automatically"),
        m_bypass_proxy("Bypass proxy server"),
        m_use_ssl("Use SSL for all the servers on this network"),
        m_accept_invalid_cert("Accept invalid SSL certificates"),
        m_use_global_user_info("Use global user information"),
        m_nickname_lbl("Nickname"),
        m_nickname_2_lbl("Second choice"),
        m_realname_lbl("Real name"),
        m_username_lbl("Username"),
        m_login_method_lbl("Login method"),
        m_password_lbl("Password"),
        m_charset_lbl("Character set"),
        m_close_btn("Close") {
    add(m_contents);
    NetworkListDialog::set_margins(m_contents);

    m_contents.set_spacing(8);
    m_contents.pack_start(m_tab_contents);
    m_contents.pack_start(m_selected_server_only, Gtk::PACK_SHRINK);
    m_contents.pack_start(m_auto_conn_network, Gtk::PACK_SHRINK);
    m_contents.pack_start(m_bypass_proxy, Gtk::PACK_SHRINK);
    m_contents.pack_start(m_use_ssl, Gtk::PACK_SHRINK);
    m_contents.pack_start(m_accept_invalid_cert, Gtk::PACK_SHRINK);
    m_contents.pack_start(m_use_global_user_info, Gtk::PACK_SHRINK);
    m_contents.pack_start(m_user_info, Gtk::PACK_SHRINK);
    m_contents.pack_start(m_actions, Gtk::PACK_SHRINK);

    m_tab_contents.set_spacing(8);
    m_tab_contents.pack_start(m_tabs);
    m_tabs.append_page(m_server_list_scroller, m_server_lbl);
    m_tabs.append_page(m_autojoin_list_scroller, m_autojoin_lbl);
    m_tabs.append_page(m_connect_cmds_list_scroller, m_connect_cmds_lbl);
    m_tab_contents.pack_start(m_edit_actions, Gtk::PACK_SHRINK);
    m_edit_actions.set_spacing(8);
    m_edit_actions.pack_start(m_add_btn, Gtk::PACK_SHRINK);
    m_edit_actions.pack_start(m_del_btn, Gtk::PACK_SHRINK);
    m_server_list_scroller.add(m_server_list);
    m_autojoin_list_scroller.add(m_autojoin_list);
    m_connect_cmds_list_scroller.add(m_connect_cmds_list);

    m_server_list.set_model(m_servers_model);
    m_server_list.set_headers_visible(false);

    m_server_selected_column.pack_start(m_server_selected_renderer);
    m_server_selected_column.set_renderer(m_server_selected_renderer, m_server_columns.m_selected);
    m_server_list.append_column(m_server_selected_column);

    m_server_column.pack_start(m_server_renderer);
    m_server_column.set_renderer(m_server_renderer, m_server_columns.m_server);
    m_server_renderer.property_editable() = true;
    m_server_list.append_column(m_server_column);

    m_autojoin_list.set_model(m_channels_model);

    m_channel_column.set_title("Channel");
    m_channel_column.pack_start(m_channel_renderer);
    m_channel_column.set_renderer(m_channel_renderer, m_channel_columns.m_name);
    m_channel_renderer.property_editable() = true;
    m_autojoin_list.append_column(m_channel_column);

    m_password_column.set_title("Password (Key)");
    m_password_column.pack_start(m_password_renderer);
    m_password_column.set_renderer(m_password_renderer, m_channel_columns.m_password);
    m_password_renderer.property_editable() = true;
    m_autojoin_list.append_column(m_password_column);

    m_connect_cmds_list.set_model(m_commands_model);
    m_connect_cmds_list.set_headers_visible(false);

    m_command_column.pack_start(m_command_renderer);
    m_command_column.set_renderer(m_command_renderer, m_command_columns.m_command);
    m_command_renderer.property_editable() = true;
    m_connect_cmds_list.append_column(m_command_column);

    m_user_info.set_row_spacing(8);
    m_user_info.set_column_spacing(8);
    m_user_info.attach(m_nickname_lbl, 0, 0, 1, 1);
    m_user_info.attach(m_nickname_fld, 1, 0, 1, 1);
    m_user_info.attach(m_nickname_2_lbl, 0, 1, 1, 1);
    m_user_info.attach(m_nickname_2_fld, 1, 1, 1, 1);
    m_user_info.attach(m_realname_lbl, 0, 2, 1, 1);
    m_user_info.attach(m_realname_fld, 1, 2, 1, 1);
    m_user_info.attach(m_username_lbl, 0, 3, 1, 1);
    m_user_info.attach(m_username_fld, 1, 3, 1, 1);
    m_user_info.attach(m_login_method_lbl, 0, 4, 1, 1);
    m_user_info.attach(m_login_method_picker, 1, 4, 1, 1);
    m_user_info.attach(m_password_lbl, 0, 5, 1, 1);
    m_user_info.attach(m_password_fld, 1, 5, 1, 1);
    m_user_info.attach(m_charset_lbl, 0, 6, 1, 1);
    m_user_info.attach(m_charset_picker, 1, 6, 1, 1);

    m_nickname_lbl.set_halign(Gtk::ALIGN_END);
    m_nickname_2_lbl.set_halign(Gtk::ALIGN_END);
    m_realname_lbl.set_halign(Gtk::ALIGN_END);
    m_username_lbl.set_halign(Gtk::ALIGN_END);
    m_login_method_lbl.set_halign(Gtk::ALIGN_END);
    m_password_lbl.set_halign(Gtk::ALIGN_END);
    m_charset_lbl.set_halign(Gtk::ALIGN_END);

    m_nickname_fld.set_halign(Gtk::ALIGN_FILL);
    m_nickname_fld.set_hexpand(true);
    m_nickname_2_fld.set_halign(Gtk::ALIGN_FILL);
    m_nickname_2_fld.set_hexpand(true);
    m_realname_fld.set_halign(Gtk::ALIGN_FILL);
    m_realname_fld.set_hexpand(true);
    m_username_fld.set_halign(Gtk::ALIGN_FILL);
    m_username_fld.set_hexpand(true);
    m_login_method_picker.set_halign(Gtk::ALIGN_FILL);
    m_login_method_picker.set_hexpand(true);
    m_password_fld.set_halign(Gtk::ALIGN_FILL);
    m_password_fld.set_hexpand(true);
    m_charset_picker.set_halign(Gtk::ALIGN_FILL);
    m_charset_picker.set_hexpand(true);

    m_actions.set_spacing(8);
    m_actions.set_halign(Gtk::ALIGN_END);
    m_actions.pack_end(m_close_btn);

    on_selection_changed(m_server_list.get_selection());
    on_tab_changed(0);
    m_tabs.signal_switch_page().connect([&] (Widget *, guint i) {
        if (m_closing) {
            on_tab_changed(i);
        }
    });
}

NetworkEditDialog::~NetworkEditDialog() {
    m_closing = true;
}

void NetworkEditDialog::on_tab_changed(unsigned index) {
    m_sel_changed.disconnect();
    Glib::RefPtr<Gtk::TreeSelection> selection;
    switch (index) {
        case 0:
            selection = m_server_list.get_selection();
            m_add_handler = [&] (core::Network &n) { on_add_server(n); };
            m_remove_handler = [&] (core::Network &n) { on_remove_server(n); };
            break;
        case 1:
            selection = m_autojoin_list.get_selection();
            m_add_handler = [&] (core::Network &n) { on_add_channel(n); };
            m_remove_handler = [&] (core::Network &n) { on_remove_channel(n); };
            break;
        case 2:
            selection = m_connect_cmds_list.get_selection();
            m_add_handler = [&] (core::Network &n) { on_add_command(n); };
            m_remove_handler = [&] (core::Network &n) { on_remove_command(n); };
            break;
    }
    m_sel_changed = on_selection_changed(selection);
}

sigc::connection NetworkEditDialog::on_selection_changed(Glib::RefPtr<Gtk::TreeSelection> selection) {
    m_del_btn.set_sensitive(selection->get_selected());
    return selection->signal_changed().connect([=] () {
        m_del_btn.set_sensitive(selection->get_selected());
    });
}

void NetworkEditDialog::edit(core::Network &network) {
    set_title(network.name + " - dIRC");
    show_all();

    m_server_toggled.disconnect();
    m_server_toggled = m_server_selected_renderer.signal_toggled().connect(
        [&] (const Glib::ustring &path) {
            on_server_toggled(path, network);
        });

    m_server_edited.disconnect();
    m_server_edited = m_server_renderer.signal_edited().connect(
        [&] (const Glib::ustring &path, const Glib::ustring &value) {
            on_server_edited(path, value, network);
        });

    populate_servers(network);

    m_channel_edited.disconnect();
    m_channel_edited = m_channel_renderer.signal_edited().connect(
        [&] (const Glib::ustring &path, const Glib::ustring &value) {
            on_channel_edited(path, value, network);
        });

    m_password_edited.disconnect();
    m_password_edited = m_password_renderer.signal_edited().connect(
        [&] (const Glib::ustring &path, const Glib::ustring &value) {
            on_password_edited(path, value, network);
        });

    populate_channels(network);

    m_command_edited.disconnect();
    m_command_edited = m_command_renderer.signal_edited().connect(
        [&] (const Glib::ustring &path, const Glib::ustring &value) {
            on_command_edited(path, value, network);
        });

    populate_commands(network);

    m_add_clicked.disconnect();
    m_add_clicked = m_add_btn.signal_clicked().connect([&] {
        m_add_handler(network);
    });

    m_del_clicked.disconnect();
    m_del_clicked = m_del_btn.signal_clicked().connect([&] {
        m_remove_handler(network);
    });

    m_selected_server_only.set_active(network.connect_selected_server_only);
    m_selected_server_only_toggled.disconnect();
    m_selected_server_only_toggled = m_selected_server_only.signal_toggled().connect(
        [&] () {
            network.connect_selected_server_only = m_selected_server_only.get_active();
        });

    m_auto_conn_network.set_active(network.connect_automatically);
    m_auto_conn_network_toggled.disconnect();
    m_auto_conn_network_toggled = m_auto_conn_network.signal_toggled().connect(
        [&] () {
            network.connect_automatically = m_auto_conn_network.get_active();
        });

    m_bypass_proxy.set_active(network.bypass_proxy);
    m_bypass_proxy_toggled.disconnect();
    m_bypass_proxy_toggled = m_bypass_proxy.signal_toggled().connect(
        [&] () {
            network.bypass_proxy = m_bypass_proxy.get_active();
        });

    m_use_ssl.set_active(network.use_ssl);
    m_use_ssl_toggled.disconnect();
    m_use_ssl_toggled = m_use_ssl.signal_toggled().connect(
        [&] () {
            network.use_ssl = m_use_ssl.get_active();
        });

    m_accept_invalid_cert.set_active(network.accept_invalid_ssl_cert);
    m_accept_invalid_cert_toggled.disconnect();
    m_accept_invalid_cert_toggled = m_accept_invalid_cert.signal_toggled().connect(
        [&] () {
            network.accept_invalid_ssl_cert = m_accept_invalid_cert.get_active();
        });

    on_global_user_info();
    m_use_global_user_info.set_active(network.use_global_user_info);
    m_use_global_user_info_toggled.disconnect();
    m_use_global_user_info_toggled = m_use_global_user_info.signal_toggled().connect(
        [&] () {
            network.use_global_user_info = m_use_global_user_info.get_active();
            on_global_user_info();
        });

    for (auto i = network.nicknames.size(); i < 3; i++) {
        network.nicknames.push_back("");
    }
    m_nickname_fld.set_text(network.nicknames[0]);
    m_nickname_chgd.disconnect();
    m_nickname_chgd = m_nickname_fld.signal_changed().connect([&] () {
        network.nicknames[0] = m_nickname_fld.get_text();
    });
    m_nickname_2_fld.set_text(network.nicknames[1]);
    m_nickname_2_chgd.disconnect();
    m_nickname_2_chgd = m_nickname_2_fld.signal_changed().connect([&] () {
        network.nicknames[1] = m_nickname_2_fld.get_text();
    });

    m_realname_fld.set_text(network.realname);
    m_realname_chgd.disconnect();
    m_realname_chgd = m_realname_fld.signal_changed().connect([&] () {
        network.realname = m_realname_fld.get_text();
    });

    m_username_fld.set_text(network.realname);
    m_username_chgd.disconnect();
    m_username_chgd = m_username_fld.signal_changed().connect([&] () {
        network.realname = m_username_fld.get_text();
    });
}

void NetworkEditDialog::populate_servers(core::Network &network) {
    m_servers_model->clear();
    m_selected_server = -1;
    unsigned i = 0;
    for (auto it = network.servers.begin(); it != network.servers.end(); it++, i++) {
        auto row = *m_servers_model->append();
        populate_server(row, *it, i);
    }
}

void NetworkEditDialog::populate_server(Gtk::TreeRow &row, core::Server &server, unsigned i) {
    row[m_server_columns.m_selected] = server.selected && m_selected_server == -1;
    if (m_selected_server == -1) {
        m_selected_server = int(i);
    }
    else {
        server.selected = false;
    }
    row[m_server_columns.m_server] =
            server.hostname +
            (server.port > 0 ? "/" + std::to_string(server.port) : "");
}

void NetworkEditDialog::populate_channels(core::Network &network) {
    m_channels_model->clear();
    for (auto it = network.autojoin_channels.begin(); it != network.autojoin_channels.end(); it++) {
        auto row = *m_channels_model->append();
        populate_channel(row, *it);
    }
}

void NetworkEditDialog::populate_channel(Gtk::TreeRow &row, core::Channel &channel) {
    row[m_channel_columns.m_name] = channel.name;
    row[m_channel_columns.m_password] = channel.key;
}

void NetworkEditDialog::populate_commands(core::Network &network) {
    m_commands_model->clear();
    for (auto it = network.connect_commands.begin(); it != network.connect_commands.end(); it++) {
        auto row = *m_commands_model->append();
        populate_command(row, *it);
    }
}

void NetworkEditDialog::populate_command(Gtk::TreeRow &row, std::string &command) {
    row[m_command_columns.m_command] = command;
}

void NetworkEditDialog::on_global_user_info() {
    bool enabled = !m_use_global_user_info.get_active();
    m_nickname_lbl.set_sensitive(enabled);
    m_nickname_fld.set_sensitive(enabled);
    m_nickname_2_lbl.set_sensitive(enabled);
    m_nickname_2_fld.set_sensitive(enabled);
    m_realname_lbl.set_sensitive(enabled);
    m_realname_fld.set_sensitive(enabled);
    m_username_lbl.set_sensitive(enabled);
    m_username_lbl.set_sensitive(enabled);
}

void NetworkEditDialog::on_server_toggled(const Glib::ustring &s_path, core::Network &network) {
    auto it = m_servers_model->get_iter(s_path);
    auto path = m_servers_model->get_path(it);
    unsigned i = unsigned(path[0]);
    core::Server &server = network.servers[i];

    if (m_selected_server != -1) {
        auto oit = m_servers_model->children().begin();
        auto nit = network.servers.begin();
        for (int i = 0; i < m_selected_server; i++, oit++, nit++);
        (*oit)[m_server_columns.m_selected] = false;
        nit->selected = false;
    }

    server.selected = !server.selected;
    m_selected_server = server.selected ? int(i) : -1;
    (*it)[m_server_columns.m_selected] = server.selected;
}

void NetworkEditDialog::on_server_edited(const Glib::ustring &path, const Glib::ustring &value, core::Network &network) {
    boost::smatch match;
    std::string server_name = value;
    boost::regex_match(server_name, match, m_server_pattern);
    if (!match.empty()) {
        auto it = m_servers_model->get_iter(path);
        auto path = m_servers_model->get_path(it);
        unsigned i = unsigned(path[0]);
        core::Server &server = network.servers[i];
        server.hostname = match[1];
        std::string s_port = match[2];
        server.port = s_port.empty() ? 0 : std::stoul(s_port);
        (*it)[m_server_columns.m_server] =
                server.hostname +
                (server.port == 0 ? "" : "/" + std::to_string(server.port));
    }
}

void NetworkEditDialog::on_channel_edited(const Glib::ustring &s_path, const Glib::ustring &value, core::Network &network) {
    std::string name = value;
    boost::trim(name);
    if (!name.empty() && name.find(" ") == std::string::npos) {
        auto it = m_channels_model->get_iter(s_path);
        auto path = m_channels_model->get_path(it);
        unsigned i = unsigned(path[0]);
        core::Channel &channel = network.autojoin_channels[i];
        (*it)[m_channel_columns.m_name] = name;
        channel.name = name;
    }
}

void NetworkEditDialog::on_password_edited(const Glib::ustring &s_path, const Glib::ustring &value, core::Network &network) {
    std::string password = value;
    boost::trim(password);
    if (password.find(" ") == std::string::npos) {
        auto it = m_channels_model->get_iter(s_path);
        auto path = m_channels_model->get_path(it);
        unsigned i = unsigned(path[0]);
        core::Channel &channel = network.autojoin_channels[i];
        (*it)[m_channel_columns.m_password] = password;
        channel.key = password;
    }
}

void NetworkEditDialog::on_command_edited(const Glib::ustring &s_path, const Glib::ustring &value, core::Network &network) {
    std::string command = value;
    boost::trim(command);
    if (!command.empty()) {
        auto it = m_commands_model->get_iter(s_path);
        auto path = m_commands_model->get_path(it);
        unsigned i = unsigned(path[0]);
        std::string &cmd = network.connect_commands[i];
        (*it)[m_command_columns.m_command] = command;
        cmd = command;
    }
}

void NetworkEditDialog::on_add_server(core::Network &network) {
    unsigned n = unsigned(network.servers.size());
    network.servers.push_back(core::Server());
    core::Server &server = network.servers.back();
    server.hostname = "0.0.0.0";
    auto row = *m_servers_model->append();
    populate_server(row, server, n);
}

void NetworkEditDialog::on_add_channel(core::Network &network) {
    network.autojoin_channels.push_back(core::Channel());
    core::Channel &channel = network.autojoin_channels.back();
    channel.name = "<channel>";
    auto row = *m_channels_model->append();
    populate_channel(row, channel);
}

void NetworkEditDialog::on_add_command(core::Network &network) {
    network.connect_commands.push_back("<command>");
    std::string &cmd = network.connect_commands.back();
    auto row = *m_commands_model->append();
    populate_command(row, cmd);
}

void NetworkEditDialog::on_remove_server(core::Network &network) {
    auto it = m_server_list.get_selection()->get_selected();
    if (it) {
        auto path = m_servers_model->get_path(it);
        unsigned i = unsigned(path[0]);
        network.servers.erase(network.servers.begin() + i);
        m_servers_model->erase(it);
    }
}

void NetworkEditDialog::on_remove_channel(core::Network &network) {
    auto it = m_autojoin_list.get_selection()->get_selected();
    if (it) {
        auto path = m_channels_model->get_path(it);
        unsigned i = unsigned(path[0]);
        network.autojoin_channels.erase(network.autojoin_channels.begin() + i);
        m_channels_model->erase(it);
    }
}

void NetworkEditDialog::on_remove_command(core::Network &network) {
    auto it = m_connect_cmds_list.get_selection()->get_selected();
    if (it) {
        auto path = m_commands_model->get_path(it);
        unsigned i = unsigned(path[0]);
        network.connect_commands.erase(network.connect_commands.begin() + i);
        m_commands_model->erase(it);
    }
}

}
