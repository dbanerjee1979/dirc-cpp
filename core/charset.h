#ifndef CHARSET_H
#define CHARSET_H

namespace core {

class Charset {
public:
    Charset() {}
    virtual ~Charset() {}
    virtual const std::string &description() const = 0;
};

}

#endif // CHARSET_H
