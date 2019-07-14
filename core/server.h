#ifndef SERVER_H
#define SERVER_H

#include <string>

namespace core {

struct Server {
    std::string hostname;
    unsigned long port;
    bool selected;

    Server() :
        port(0),
        selected(false) {
    }
};

}

#endif // SERVER_H
