#include "network_list_dialog.h"

namespace gtk {

NetworkListDialog::NetworkListDialog() {
    set_title("Network List - dIRC");
}

void NetworkListDialog::edit(core::DircConfig &config) {
    show_all();
}

}
