#include "network_edit_dialog.h"
#include "network_list_dialog.h"

namespace gtk {

NetworkEditDialog::NetworkEditDialog() :
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

}
