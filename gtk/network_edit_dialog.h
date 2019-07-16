#ifndef NETWORK_EDIT_DIALOG_H
#define NETWORK_EDIT_DIALOG_H

#include <functional>
#include <string>
#include <gtkmm.h>
#include <boost/regex.hpp>
#include <core/network.h>

namespace gtk {

class ServerColumns : public Gtk::TreeModel::ColumnRecord {
public:
    ServerColumns();

    Gtk::TreeModelColumn<bool> m_selected;
    Gtk::TreeModelColumn<std::string> m_server;
};

class ChannelColumns : public Gtk::TreeModel::ColumnRecord {
public:
    ChannelColumns();

    Gtk::TreeModelColumn<std::string> m_name;
    Gtk::TreeModelColumn<std::string> m_password;
};

class CommandColumns : public Gtk::TreeModel::ColumnRecord {
public:
    CommandColumns();

    Gtk::TreeModelColumn<std::string> m_command;
};

class NetworkEditDialog : public Gtk::Window {
public:
    NetworkEditDialog();
    virtual ~NetworkEditDialog();
    void edit(core::Network &network);
private:
    void populate_servers(core::Network &network);
    void populate_server(Gtk::TreeRow &row, core::Server &server, unsigned i);
    void populate_channels(core::Network &network);
    void populate_channel(Gtk::TreeRow &row, core::Channel &channel);
    void populate_commands(core::Network &network);
    void populate_command(Gtk::TreeRow &row, std::string &command);
    void on_global_user_info();
    void on_server_toggled(const Glib::ustring &path, core::Network &network);
    void on_server_edited(const Glib::ustring &path, const Glib::ustring &value, core::Network &network);
    void on_channel_edited(const Glib::ustring &path, const Glib::ustring &value, core::Network &network);
    void on_password_edited(const Glib::ustring &path, const Glib::ustring &value, core::Network &network);
    void on_command_edited(const Glib::ustring &path, const Glib::ustring &value, core::Network &network);
    void on_tab_changed(unsigned index);
    sigc::connection on_selection_changed(Glib::RefPtr<Gtk::TreeSelection> selection);
    void on_add_item(core::Network &network);
    void on_add_server(core::Network &network);
    void on_add_channel(core::Network &network);
    void on_add_command(core::Network &network);
    void on_remove_item(core::Network &network);
    void on_remove_server(core::Network &network);
    void on_remove_channel(core::Network &network);
    void on_remove_command(core::Network &network);

    bool m_closing;
    boost::regex m_server_pattern;
    int m_selected_server;
    ServerColumns m_server_columns;
    ChannelColumns m_channel_columns;
    CommandColumns m_command_columns;
    Glib::RefPtr<Gtk::ListStore> m_servers_model;
    Glib::RefPtr<Gtk::ListStore> m_channels_model;
    Glib::RefPtr<Gtk::ListStore> m_commands_model;
    std::function<void(core::Network &)> m_add_handler;
    std::function<void(core::Network &)> m_remove_handler;

    Gtk::VBox m_contents;
    Gtk::HBox m_tab_contents;
    Gtk::Notebook m_tabs;
    Gtk::Label m_server_lbl;
    Gtk::ScrolledWindow m_server_list_scroller;
    Gtk::TreeView m_server_list;
    Gtk::TreeViewColumn m_server_selected_column;
    Gtk::CellRendererToggle m_server_selected_renderer;
    sigc::connection m_server_toggled;
    Gtk::TreeViewColumn m_server_column;
    Gtk::CellRendererText m_server_renderer;
    sigc::connection m_server_edited;
    Gtk::Label m_autojoin_lbl;
    Gtk::ScrolledWindow m_autojoin_list_scroller;
    Gtk::TreeView m_autojoin_list;
    Gtk::TreeViewColumn m_channel_column;
    Gtk::CellRendererText m_channel_renderer;
    sigc::connection m_channel_edited;
    Gtk::TreeViewColumn m_password_column;
    Gtk::CellRendererText m_password_renderer;
    sigc::connection m_password_edited;
    Gtk::Label m_connect_cmds_lbl;
    Gtk::ScrolledWindow m_connect_cmds_list_scroller;
    Gtk::TreeView m_connect_cmds_list;
    Gtk::TreeViewColumn m_command_column;
    Gtk::CellRendererText m_command_renderer;
    sigc::connection m_command_edited;
    Gtk::VBox m_edit_actions;
    Gtk::Button m_add_btn;
    sigc::connection m_add_clicked;
    Gtk::Button m_del_btn;
    sigc::connection m_sel_changed;
    sigc::connection m_del_clicked;
    Gtk::CheckButton m_selected_server_only;
    sigc::connection m_selected_server_only_toggled;
    Gtk::CheckButton m_auto_conn_network;
    sigc::connection m_auto_conn_network_toggled;
    Gtk::CheckButton m_bypass_proxy;
    sigc::connection m_bypass_proxy_toggled;
    Gtk::CheckButton m_use_ssl;
    sigc::connection m_use_ssl_toggled;
    Gtk::CheckButton m_accept_invalid_cert;
    sigc::connection m_accept_invalid_cert_toggled;
    Gtk::CheckButton m_use_global_user_info;
    sigc::connection m_use_global_user_info_toggled;
    Gtk::Grid m_user_info;
    Gtk::Label m_nickname_lbl;
    Gtk::Entry m_nickname_fld;
    Gtk::Label m_nickname_2_lbl;
    Gtk::Entry m_nickname_2_fld;
    Gtk::Label m_realname_lbl;
    Gtk::Entry m_realname_fld;
    Gtk::Label m_username_lbl;
    Gtk::Entry m_username_fld;
    Gtk::Label m_login_method_lbl;
    Gtk::ComboBox m_login_method_picker;
    Gtk::Label m_password_lbl;
    Gtk::Entry m_password_fld;
    Gtk::Label m_charset_lbl;
    Gtk::ComboBox m_charset_picker;
    Gtk::HBox m_actions;
    Gtk::Button m_close_btn;
};

}

#endif // NETWORK_EDIT_DIALOG_H
