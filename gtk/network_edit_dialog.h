#ifndef NETWORK_EDIT_DIALOG_H
#define NETWORK_EDIT_DIALOG_H

#include <gtkmm.h>

namespace gtk {

class NetworkEditDialog : public Gtk::Window {
public:
    NetworkEditDialog();
private:
    Gtk::VBox m_contents;
    Gtk::HBox m_tab_contents;
    Gtk::Notebook m_tabs;
    Gtk::Label m_server_lbl;
    Gtk::ScrolledWindow m_server_list_scroller;
    Gtk::TreeView m_server_list;
    Gtk::Label m_autojoin_lbl;
    Gtk::ScrolledWindow m_autojoin_list_scroller;
    Gtk::TreeView m_autojoin_list;
    Gtk::TreeViewColumn m_channel_column;
    Gtk::TreeViewColumn m_password_column;
    Gtk::Label m_connect_cmds_lbl;
    Gtk::ScrolledWindow m_connect_cmds_list_scroller;
    Gtk::TreeView m_connect_cmds_list;
    Gtk::VBox m_edit_actions;
    Gtk::Button m_add_btn;
    Gtk::Button m_del_btn;
    Gtk::CheckButton m_selected_server_only;
    Gtk::CheckButton m_auto_conn_network;
    Gtk::CheckButton m_bypass_proxy;
    Gtk::CheckButton m_use_ssl;
    Gtk::CheckButton m_accept_invalid_cert;
    Gtk::CheckButton m_use_global_user_info;
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
