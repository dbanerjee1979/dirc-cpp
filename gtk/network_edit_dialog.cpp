#include "network_edit_dialog.h"
#include "network_list_dialog.h"
#include <boost/regex.hpp>

namespace gtk {

ServerColumns::ServerColumns() {
    add(m_selected);
    add(m_server);
}

NetworkEditDialog::NetworkEditDialog() :
        server_pattern("\\s*((?:[A-z0-9-]+\\.)*[A-z0-9-]+)(?:/([0-9]*))?\\s*"),
        m_servers_model(Gtk::ListStore::create(m_server_columns)),
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
    m_server_renderer.property_editable() = true;
    m_server_list.append_column(m_server_selected_column);

    m_server_column.pack_start(m_server_renderer);
    m_server_column.set_renderer(m_server_renderer, m_server_columns.m_server);
    m_server_renderer.property_editable() = true;
    m_server_list.append_column(m_server_column);

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
}

void NetworkEditDialog::populate_servers(core::Network &network) {
    m_servers_model->clear();
    m_selected_server = -1;
    unsigned i = 0;
    for (auto it = network.servers.begin(); it != network.servers.end(); it++, i++) {
        auto row = *m_servers_model->append();
        row[m_server_columns.m_selected] = it->selected && m_selected_server == -1;
        if (m_selected_server == -1) {
            m_selected_server = int(i);
        }
        else {
            it->selected = false;
        }
        row[m_server_columns.m_server] = it->hostname + (it->port > 0 ? "/" + std::to_string(it->port) : "");
    }
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
    boost::regex_match(server_name, match, server_pattern);
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

}
