#include "binding.h"

namespace gtk {

void Binding::bind(std::string &value, Gtk::Entry &w, sigc::connection &cn) {
    w.set_text(value);
    cn.disconnect();
    cn = w.signal_changed().connect([&] () {
        value = w.get_text();
    });
}

void Binding::bind(bool &value, Gtk::CheckButton &w, sigc::connection &cn) {
    w.set_active(value);
    cn.disconnect();
    cn = w.signal_toggled().connect([&] () {
        value = w.get_active();
    });
}

}
