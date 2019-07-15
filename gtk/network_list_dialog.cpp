#include "network_list_dialog.h"

namespace gtk {

NetworkListDialog::NetworkListDialog() :
        m_username_lbl("Username"),
        m_add_btn("Add"),
        m_del_btn("Remove"),
        m_edit_btn("Edit..."),
        m_sort_btn("Sort"),
        m_fav_btn("Favorite"),
        m_skip_net_list("Skip network list on startup"),
        m_filter_net_list("Show favorites only"),
        m_connect_btn("Connect"),
        m_close_btn("Close") {
    set_title("Network List - dIRC");

    m_nickname_lbls[0].set_text("Nickname");
    m_nickname_lbls[1].set_text("Second choice");
    m_nickname_lbls[2].set_text("Third choice");

    add(m_contents);
    set_margins(m_contents);
    m_contents.set_spacing(8);
    m_contents.pack_start(m_user_info, Gtk::PACK_SHRINK);
    m_contents.pack_start(m_net_list_contents);
    m_contents.pack_start(m_net_list_opts, Gtk::PACK_SHRINK);
    m_contents.pack_start(m_actions, Gtk::PACK_SHRINK);

    m_user_info.set_row_spacing(8);
    m_user_info.set_column_spacing(8);
    m_user_info.attach(m_nickname_lbls[0], 0, 0, 1, 1);
    m_user_info.attach(m_nickname_flds[0], 1, 0, 1, 1);
    m_user_info.attach(m_nickname_lbls[1], 0, 1, 1, 1);
    m_user_info.attach(m_nickname_flds[1], 1, 1, 1, 1);
    m_user_info.attach(m_nickname_lbls[2], 0, 2, 1, 1);
    m_user_info.attach(m_nickname_flds[2], 1, 2, 1, 1);
    m_user_info.attach(m_username_lbl, 0, 3, 1, 1);
    m_user_info.attach(m_username_fld, 1, 3, 1, 1);

    for (unsigned long i = 0; i < 3; i++) {
        m_nickname_lbls[i].set_halign(Gtk::ALIGN_END);
        m_nickname_flds[i].set_hexpand();
    }

    m_net_list_contents.set_spacing(8);
    m_net_list_contents.pack_start(m_net_list_scroller);
    m_net_list_scroller.add(m_net_list);
    m_net_list_contents.pack_start(m_net_actions, Gtk::PACK_SHRINK);

    m_net_actions.set_spacing(8);
    m_net_actions.pack_start(m_add_btn, Gtk::PACK_SHRINK);
    m_net_actions.pack_start(m_del_btn, Gtk::PACK_SHRINK);
    m_net_actions.pack_start(m_edit_btn, Gtk::PACK_SHRINK);
    m_net_actions.pack_start(m_sort_btn, Gtk::PACK_SHRINK);
    m_net_actions.pack_start(m_fav_btn, Gtk::PACK_SHRINK);

    m_net_list_opts.set_spacing(8);
    m_net_list_opts.pack_start(m_skip_net_list, Gtk::PACK_SHRINK);
    m_net_list_opts.pack_start(m_filter_net_list, Gtk::PACK_SHRINK);

    m_actions.set_spacing(8);
    m_actions.set_halign(Gtk::ALIGN_END);
    m_actions.pack_end(m_connect_btn);
    m_actions.pack_end(m_close_btn);
}

void NetworkListDialog::set_margins(Gtk::Widget &w) {
    w.set_margin_top(8);
    w.set_margin_bottom(8);
    w.set_margin_left(8);
    w.set_margin_right(8);
}

void NetworkListDialog::edit(core::DircConfig &config) {
    show_all();
}

}
