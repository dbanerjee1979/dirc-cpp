#ifndef NETWORK_LIST_DIALOG_H
#define NETWORK_LIST_DIALOG_H

#include <gtkmm.h>
#include <core/dirc_config.h>

namespace gtk {

class NetworkListDialog : public Gtk::Window {
public:
    NetworkListDialog();
    void edit(core::DircConfig &config);
    static void set_margins(Gtk::Widget &w);
private:
    Gtk::VBox m_contents;
    Gtk::Grid m_user_info;
    Gtk::Label m_nickname_lbls[3];
    Gtk::Entry m_nickname_flds[3];
    Gtk::Label m_username_lbl;
    Gtk::Entry m_username_fld;
    Gtk::HBox m_net_list_contents;
    Gtk::ScrolledWindow m_net_list_scroller;
    Gtk::TreeView m_net_list;
    Gtk::VBox m_net_actions;
    Gtk::Button m_add_btn;
    Gtk::Button m_del_btn;
    Gtk::Button m_edit_btn;
    Gtk::Button m_sort_btn;
    Gtk::Button m_fav_btn;
    Gtk::HBox m_net_list_opts;
    Gtk::CheckButton m_skip_net_list;
    Gtk::CheckButton m_filter_net_list;
    Gtk::ButtonBox m_actions;
    Gtk::Button m_connect_btn;
    Gtk::Button m_close_btn;
};

}

#endif // NETWORK_LIST_DIALOG_H
