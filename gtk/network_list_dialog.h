#ifndef NETWORK_LIST_DIALOG_H
#define NETWORK_LIST_DIALOG_H

#include <gtkmm.h>
#include <core/dirc_config.h>

namespace gtk {

class NetworkListDialog : public Gtk::Window {
public:
    NetworkListDialog();
    void edit(core::DircConfig &config);
};

}

#endif // NETWORK_LIST_DIALOG_H
