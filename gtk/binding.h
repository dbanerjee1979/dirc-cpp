#ifndef BINDING_H
#define BINDING_H

#include <string>
#include <gtkmm.h>

namespace gtk {

class Binding {
public:
    void bind(std::string &value, Gtk::Entry &w, sigc::connection &cn);
    void bind(bool &value, Gtk::CheckButton &w, sigc::connection &cn);
};

}

#endif // BINDING_H
