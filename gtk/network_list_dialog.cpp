#include <functional>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "network_list_dialog.h"

using namespace std::placeholders;

namespace gtk {

NetListColumns::NetListColumns() {
    add(m_index);
    add(m_name);
    add(m_weight);
}

NetworkListDialog::NetworkListDialog() :
        m_username_lbl("Username"),
        m_net_list_model(Gtk::ListStore::create(m_net_list_columns)),
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

    m_net_list.set_headers_visible(false);
    m_net_name_column.pack_start(m_net_name_renderer);
    m_net_name_column.set_renderer(m_net_name_renderer, m_net_list_columns.m_name);
    m_net_name_column.add_attribute(m_net_name_renderer.property_weight(), m_net_list_columns.m_weight);
    m_net_list.append_column(m_net_name_column);
    m_net_list.set_model(m_net_list_model);
    m_net_name_renderer.property_editable() = true;

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

    m_net_list.get_selection()->signal_changed().connect(
        sigc::mem_fun(*this, &NetworkListDialog::on_selection_changed));
    on_selection_changed();

    m_connect_btn.signal_clicked().connect([&] () {
        close();
    });

    m_close_btn.signal_clicked().connect([&] () {
        close();
    });
}

void NetworkListDialog::on_selection_changed() {
    auto it = m_net_list.get_selection()->get_selected();
    bool enabled = it;
    m_del_btn.set_sensitive(enabled);
    m_edit_btn.set_sensitive(enabled);
    m_fav_btn.set_sensitive(enabled);
}

void NetworkListDialog::set_margins(Gtk::Widget &w) {
    w.set_margin_top(8);
    w.set_margin_bottom(8);
    w.set_margin_left(8);
    w.set_margin_right(8);
}

void NetworkListDialog::edit(core::DircConfig &config) {
    for (auto i = config.nicknames.size(); i < 3; i++) {
        config.nicknames.push_back("");
    }
    for (unsigned i = 0; i < 3; i++) {
        m_nickname_flds[i].set_text(config.nicknames[i]);
        m_nickname_chgd[i].disconnect();
        m_nickname_chgd[i] = m_nickname_flds[i].signal_changed().connect([&, i] () {
            config.nicknames[i] = m_nickname_flds[i].get_text();
        });
    }
    m_username_fld.set_text(config.username);
    m_username_chgd.disconnect();
    m_username_chgd = m_username_fld.signal_changed().connect([&] () {
        config.username = m_username_fld.get_text();
    });

    m_net_name_edited.disconnect();
    m_net_name_edited = m_net_name_renderer.signal_edited().connect([&] (const Glib::ustring &path, const Glib::ustring &text) {
        on_name_edited(path, text, config);
    });

    m_add_clicked.disconnect();
    m_add_clicked = m_add_btn.signal_clicked().connect([&] () {
        on_network_added(config);
    });

    m_del_clicked.disconnect();
    m_del_clicked = m_del_btn.signal_clicked().connect([&] () {
        on_network_removed(config);
    });

    m_sort_clicked.disconnect();
    m_sort_clicked = m_sort_btn.signal_clicked().connect([&] () {
        on_sort_networks(config);
    });

    m_fav_clicked.disconnect();
    m_fav_clicked = m_fav_btn.signal_clicked().connect([&] () {
        on_toggle_favorite(config);
    });

    m_skip_net_list.set_active(config.skip_list_on_startup);
    m_skip_net_clicked.disconnect();
    m_skip_net_clicked = m_skip_net_list.signal_clicked().connect([&] () {
        config.skip_list_on_startup = m_skip_net_list.get_active();
    });

    m_filter_net_list.set_active(config.show_favorites);
    m_filter_clicked.disconnect();
    m_filter_clicked = m_filter_net_list.signal_clicked().connect([&] () {
        on_toggle_filter(config);
    });

    populate_list(config);

    show_all();
}

void NetworkListDialog::on_name_edited(const Glib::ustring &path, const Glib::ustring &text, core::DircConfig &config) {
    std::string name = text;
    boost::trim(name);
    if (name.length() > 0) {
        auto it = m_net_list_model->get_iter(path);
        unsigned i = (*it)[m_net_list_columns.m_index];
        (*it)[m_net_list_columns.m_name] = name;
        config.networks[i].name = name;
    }
}

void NetworkListDialog::on_network_added(core::DircConfig &config) {
    unsigned i = unsigned(config.networks.size());
    config.networks.push_back(core::Network());
    core::Network &network = config.networks.back();
    network.name = "New Network";
    network.favorite = false;
    auto row = *m_net_list_model->append();
    populate_row(row, network);
    row[m_net_list_columns.m_index] = i;
}

void NetworkListDialog::on_network_removed(core::DircConfig &config) {
    auto it = m_net_list.get_selection()->get_selected();
    if (it) {
        unsigned i = (*it)[m_net_list_columns.m_index];
        config.networks.erase(config.networks.begin() + i);
        for (auto rit = it; rit != m_net_list_model->children().end(); rit++) {
            i = (*rit)[m_net_list_columns.m_index];
            (*rit)[m_net_list_columns.m_index] = i - 1;
        }
        m_net_list_model->erase(it);
    }
}

void NetworkListDialog::on_sort_networks(core::DircConfig &config) {
    std::sort(config.networks.begin(), config.networks.end(),
            [&] (const core::Network &n1, const core::Network &n2) {
                return boost::ilexicographical_compare(n1.name, n2.name);
            });
    populate_list(config);
}

void NetworkListDialog::on_toggle_favorite(core::DircConfig &config) {
    auto it = m_net_list.get_selection()->get_selected();
    if (it) {
        unsigned i = (*it)[m_net_list_columns.m_index];
        core::Network &network = config.networks[i];
        network.favorite = !network.favorite;
        auto row = *it;
        populate_row(row, network);
    }
}

void NetworkListDialog::on_toggle_filter(core::DircConfig &config) {
    config.show_favorites = !config.show_favorites;
    populate_list(config);
}

void NetworkListDialog::populate_list(core::DircConfig &config) {
    m_net_list_model->clear();
    unsigned i = 0;
    for (auto it = config.networks.begin(); it != config.networks.end(); it++, i++) {
        if (!config.show_favorites || it->favorite) {
            auto row = *m_net_list_model->append();
            populate_row(row, *it);
            row[m_net_list_columns.m_index] = i;
        }
    }
}

void NetworkListDialog::populate_row(Gtk::TreeModel::Row &row, core::Network &network) {
    row[m_net_list_columns.m_name] = network.name;
    row[m_net_list_columns.m_weight] = network.favorite ? 500 : 0;
}

}
