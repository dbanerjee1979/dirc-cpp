#ifndef NETWORK_LIST_DIALOG_H
#define NETWORK_LIST_DIALOG_H

#include <gtkmm.h>
#include <core/dirc_config.h>

namespace gtk {

class NetListColumns : public Gtk::TreeModel::ColumnRecord {
public:
    NetListColumns();

    Gtk::TreeModelColumn<unsigned> m_index;
    Gtk::TreeModelColumn<std::string> m_name;
    Gtk::TreeModelColumn<int> m_weight;
};

class NetworkListDialog : public Gtk::Window {
public:
    NetworkListDialog();
    void edit(core::DircConfig &config);
    static void set_margins(Gtk::Widget &w);
private:
    void on_selection_changed();
    void on_name_edited(const Glib::ustring &path, const Glib::ustring &text, core::DircConfig &config);
    void on_network_added(core::DircConfig &config);
    void on_network_removed(core::DircConfig &config);
    void on_sort_networks(core::DircConfig &config);
    void on_toggle_favorite(core::DircConfig &config);
    void on_toggle_filter(core::DircConfig &config);
    void populate_list(core::DircConfig &config);
    void populate_row(Gtk::TreeModel::Row &row, core::Network &network);

    Gtk::VBox m_contents;
    Gtk::Grid m_user_info;
    Gtk::Label m_nickname_lbls[3];
    Gtk::Entry m_nickname_flds[3];
    sigc::connection m_nickname_chgd[3];
    Gtk::Label m_username_lbl;
    Gtk::Entry m_username_fld;
    sigc::connection m_username_chgd;
    Gtk::HBox m_net_list_contents;
    Gtk::ScrolledWindow m_net_list_scroller;
    Gtk::TreeView m_net_list;
    NetListColumns m_net_list_columns;
    Gtk::TreeViewColumn m_net_name_column;
    Gtk::CellRendererText m_net_name_renderer;
    sigc::connection m_net_name_edited;
    Glib::RefPtr<Gtk::ListStore> m_net_list_model;
    Gtk::VBox m_net_actions;
    Gtk::Button m_add_btn;
    sigc::connection m_add_clicked;
    Gtk::Button m_del_btn;
    sigc::connection m_del_clicked;
    Gtk::Button m_edit_btn;
    Gtk::Button m_sort_btn;
    sigc::connection m_sort_clicked;
    Gtk::Button m_fav_btn;
    sigc::connection m_fav_clicked;
    Gtk::HBox m_net_list_opts;
    Gtk::CheckButton m_skip_net_list;
    Gtk::CheckButton m_filter_net_list;
    sigc::connection m_filter_clicked;
    Gtk::ButtonBox m_actions;
    Gtk::Button m_connect_btn;
    Gtk::Button m_close_btn;
};

}

#endif // NETWORK_LIST_DIALOG_H
